#include "StandardProfile.h"

StandardProfile::StandardProfile(hpreal module, hpreal pressureAngle, // pressureAngle = Profilwinkel
		hpreal filletRadius,                                          // filletRadius = Fußrundungsradius
		hpreal bottomClearance) :                                     // bottomClearance = Kopfspiel
		module_(module), pressureAngle_(pressureAngle), filletRadius_(
				filletRadius), bottomClearance_(bottomClearance) {
	// Angle has to be smaller than approximately 38.146 degrees or 0.785 rad
	if (tan(pressureAngle_) > M_PI / 4)
		std::cerr << "ERROR: Your angle is too big with " << pressureAngle_
				<< std::endl;
	if (filletRadius_ > bottomClearance_ / (1 - sin(pressureAngle_))
			|| filletRadius_
					> (sin(pressureAngle_) / (1 - sin(pressureAngle_)))
							* (((M_PI - 4 * tan(pressureAngle_)) / 4
									* tan(pressureAngle_)) * module_ - bottomClearance_))
		std::cerr << "ERROR: Your filletRadius is too big with "
				<< filletRadius_ << std::endl;
}

void StandardProfile::normalize(hpreal& x) const {
	x /= (module_ * M_PI);
	// Modulo
	while (x - 1.0 > 0) {
		x -= 1.0;
	}
	// Spiegeln
	if (x > 0.5) {
		x = 1.0 - x;
	}
	x *= (module_ * M_PI);
}

void StandardProfile::calcRootCircleCenter(hpreal *center) const {
	hpreal t = (bottomClearance_ + filletRadius_ * (1 + sin(pressureAngle_)))
			/ cos(pressureAngle_);
	center[0] = module_ * M_PI + cos(pressureAngle_) * filletRadius_
			+ t * sin(pressureAngle_);
	center[1] = sin(pressureAngle_) * filletRadius_ - t * cos(pressureAngle_);
}

/**
 * Calculates the profiel for one gear pitch.
 * hpreal x has to be bigger than or equal 0.
 * When x = 0 the height at the center of a tooth
 * of the gear is calculated.
 * When x = pitch / 2 the height at the center of
 * the gap between two teeth is calculated.
 */
hpreal StandardProfile::getHeight(hpreal x) const {
	/* Values are only calculated of one half of a pitch.
	 * Therefore x is converted to values in [0, m * pi / 2], with
	 * m = module. The second half of the pitch is mirrored and
	 * therefore we start for x = 0 at a center of one pitch.
	 * x_1, ..., x_5 are used for the different regions of a pitch:
	 * 
	 * 0   <= x < x_1  --> right half of top land
	 * x_1 <= x < x_2  --> flank without bottomClearance
	 * x_2 <= x < x_3  --> rest of flank until root circle is starting
	 * x_3 <= x < x_4  --> region of root circle
	 * x_4 <= x < x_5  --> left bottom land (until center of bottom land)
	 */
	normalize(x);

	//calculate x-function for half of one pitch

	hpreal x_1 = (module_ * M_PI) / 4 - tan(pressureAngle_) * module_;
	hpreal x_2 = (module_ * M_PI) / 4 + tan(pressureAngle_) * module_;
	hpreal x_3 = x_2
			+ (bottomClearance_ + filletRadius_ * (sin(pressureAngle_) - 1))
					* tan(pressureAngle_);
	hpreal x_4 = x_3 + filletRadius_ * cos(pressureAngle_);
	hpreal x_5 = (module_ * M_PI) / 2;

	hpreal center[2];
	calcRootCircleCenter(center);

	if (x < x_1)
		return module_;
	else if (x < x_3)
		return (x - (module_ * M_PI) / 4)
				* (-cos(pressureAngle_) / sin(pressureAngle_));
	else if (x < x_4)
		return (center[1]
				- sqrt(
						filletRadius_ * filletRadius_
								- (x - center[0]) * (x - center[0])));
	else
		return -module_ - bottomClearance_;
}

void StandardProfile::getProfilePartition(std::vector<glm::vec2>& partition,
		int numberSamples) {
	for (int i = 0; i < numberSamples; i++) {
		hpreal x = ((hpreal) i / (hpreal) numberSamples) * module_ * M_PI;
		hpreal y = getHeight(x);
		partition.push_back(glm::vec2(x, y));
	}

}
