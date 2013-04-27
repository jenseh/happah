#include "happah/geometries/gears/StandardProfile.h"

StandardProfile::StandardProfile(hpreal module, hpreal pressureAngle, // pressureAngle = Profilwinkel
		hpreal filletRadius,                                          // filletRadius = Fußrundungsradius
		hpreal bottomClearance) :                                     // bottomClearance = Kopfspiel
		m_module(module), m_pressureAngle(pressureAngle), m_filletRadius(
				filletRadius), m_bottomClearance(bottomClearance) {
	// Angle has to be smaller than approximately 38.146 degrees or 0.785 rad
	if (tan(m_pressureAngle) > M_PI / 4)
		std::cerr << "ERROR: Your angle is too big with " << m_pressureAngle
				<< std::endl;
	if (m_filletRadius > m_bottomClearance / (1 - sin(m_pressureAngle))
			|| m_filletRadius
					> (sin(m_pressureAngle) / (1 - sin(m_pressureAngle)))
							* (((M_PI - 4 * tan(m_pressureAngle)) / 4
									* tan(m_pressureAngle)) * m_module - m_bottomClearance))
		std::cerr << "ERROR: Your filletRadius is too big with "
				<< m_filletRadius << std::endl;
}

void StandardProfile::normalize(hpreal& x) const {
	x /= (m_module * M_PI);
	// Modulo
	while (x - 1.0 > 0) {
		x -= 1.0;
	}
	// Spiegeln
	if (x > 0.5) {
		x = 1.0 - x;
	}
	x *= (m_module * M_PI);
}

void StandardProfile::calcRootCircleCenter(hpreal *center) const {
	hpreal t = (m_bottomClearance + m_filletRadius * (1 + sin(m_pressureAngle)))
			/ cos(m_pressureAngle);
	center[0] = m_module * M_PI + cos(m_pressureAngle) * m_filletRadius
			+ t * sin(m_pressureAngle);
	center[1] = sin(m_pressureAngle) * m_filletRadius - t * cos(m_pressureAngle);
}

/**
 * Calculates the profile for one gear pitch.
 * x has to be bigger than or equal to 0.
 * When x = 0 the height at the center of a tooth
 * of the gear is calculated.
 * When x = pitch / 2 the height at the center of
 * the gap between two teeth is calculated.
 *
 * Returns a height value in the range [-module - bottomClearance; module]
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

	hpreal x_1 = (m_module * M_PI) / 4 - tan(m_pressureAngle) * m_module;
	hpreal x_2 = (m_module * M_PI) / 4 + tan(m_pressureAngle) * m_module;
	hpreal x_3 = x_2
			+ (m_bottomClearance + m_filletRadius * (sin(m_pressureAngle) - 1))
					* tan(m_pressureAngle);
	hpreal x_4 = x_3 + m_filletRadius * cos(m_pressureAngle);
	//hpreal x_5 = (m_module * M_PI) / 2; //TODO: Katja should take a look at this unused line

	hpreal center[2];
	calcRootCircleCenter(center);

	if (x < x_1)
		return m_module;
	else if (x < x_3)
		return (x - (m_module * M_PI) / 4)
				* (-cos(m_pressureAngle) / sin(m_pressureAngle));
	else if (x < x_4)
		return (center[1]
				- sqrt(
						m_filletRadius * m_filletRadius
								- (x - center[0]) * (x - center[0])));
	else
		return -m_module - m_bottomClearance;
}

hpreal StandardProfile::getMaxHeight() const {
	return m_module;
}


hpreal StandardProfile::getModule() const {
	return m_module;
}

hpreal StandardProfile::getPressureAngle() const {
	return m_pressureAngle;
}


// Returns a vector of 2d profile points of one partition. x values are in the range [0; module*PI]
void StandardProfile::getProfilePartition(std::vector<hpvec2>& partition) {
    int numberSamples = partition.capacity();
	for (int i = 0; i < numberSamples; i++) {
		hpreal x = ((hpreal) i / (hpreal) numberSamples) * m_module * M_PI;
		partition.push_back(hpvec2(x,  getHeight(x)));
	}
}

void StandardProfile::getToothSpaceProfile(std::vector<hpvec2>& partition) {
    int numberSamples = partition.capacity();
    hpreal halfLength = m_module * M_PI * 0.5;
	for (int i = 0; i < numberSamples; i++) {
		hpreal x = ((hpreal) i / (hpreal) numberSamples) * m_module * M_PI;
		hpreal y = getHeight(x);
		partition.push_back(hpvec2(x - halfLength, y));
	}
}
