#ifndef INVOLUTEGEAR_H
#define INVOLUTEGEAR_H

#include <cstring>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

using namespace std;

#include "happah/geometries/gears/BSplineGearCurve.h"
#include "happah/geometries/gears/CylindricalGear.h"
#include "happah/geometries/gears/SimpleGear.h"
#include "happah/geometries/Mesh.h"
#include "happah/HappahTypes.h"

/** @class InvoluteGear
 * @brief Involute gear without a helix angle and with the right-hand flank
 * being an reflection of the left-hand flank.
 *
 * The values given in the constructor are based on the parameters specified
 * in the DIN 3960
 * 
 * As there are many dependent values, it is not so easy to find any with
 * which it is possible to construct an involute gear. Therefore the
 * constructor includes some values that will work.
 * Besides the "getPossibleXXX()" methods allow to calculate the range for
 * other suitable values for XXX, so that an involute gear can be constructed.
 *
 * Gears whose right-hand flank isn't a reflection to the left-hand one, have
 * to use other getToothProfile() and getGearProfile() methods, as both use
 * the reflection property.
 */

class InvoluteGear;
typedef shared_ptr<InvoluteGear> InvoluteGear_ptr;

class InvoluteGear : public CylindricalGear {
public:
	InvoluteGear(hpuint nTeeth = 15,
			hpreal module = 0.13,
			hpreal facewidth = 0.2f,
			hpreal pressureAngle = M_PI / 6.0f,
			hpreal bottomClearance = 0.0002f,
			hpreal filletRadius = 0.0f,
			hpreal helixAngle = 0.0f);

	InvoluteGear(const InvoluteGear& other);

	~InvoluteGear();

	InvoluteGear& operator=(const InvoluteGear& other);

    hpuint getNumberOfTeeth();
    hpreal getModule();
    hpreal getFacewidth(); //Zahnradbreite
    hpreal getPressureAngle(); //Eingriffswinkel - Winkel an Flanke
    hpreal getBottomClearance(); //Kopfspielhöhe
    hpreal getFilletRadius(); //Fußrundungsradius
    hpreal getHelixAngle(); //Schrägungswinkel beta
    hpreal getReferenceRadius(); //Teilkreisradius
    hpreal getTipRadius(); //Kopfkreisradius
    hpreal getRootRadius(); //Fußkreisradius
    hpreal getBaseRadius(); //Grundkreisradius
    hpreal getAngularPitch(); //Teilungswinkel

    /* getPossibleXXX methods return pointer to two values:
     * first one is minimum, second one is maximum for parameter XXX
     * with the current values.
     * If minimum > maximum no value is found.
     * methods start from the promise that current gear is a valid gear
     */
    hpuint* getPossibleNumbersOfTeeth();
    hpreal* getPossibleModules();
    hpreal* getPossiblePressureAngles();
    hpreal* getPossibleBottomClearances();
    hpreal* getPossibleFilletRadien();

    // Values are only set, if they would produce proper gear.
    // The bool returned shows if value could be set.
    bool setNumberOfTeeth(hpuint nTeeth);
    bool setModule(hpreal module);
    bool setFacewidth(hpreal facewidth);
    bool setPressureAngle(hpreal pressureAngle);
    bool setBottomClearance(hpreal bottomClearance);
    bool setFilletRadius(hpreal filletRadius);
    bool setHelixAngle(hpreal helixAngle);

    void getToothSpaceProfile(vector<hpvec2> &profile) const;
    vector<hpvec2>* getToothProfile();
    TriangleMesh* toTriangleMesh();
    SimpleGear* toSimpleGear();

    string toString();

private:
    hpuint m_nTeeth;
    hpreal m_module;
    hpreal m_facewidth;
    hpreal m_pressureAngle;
    hpreal m_bottomClearance;
    hpreal m_filletRadius;
    hpreal m_helixAngle;

    template <class T> T *getPossibleValues(T &testParameter, T minSize, T maxSize, T sampleSize);

    bool verifyConstraints(bool print = false); //Testet ob Evolventenzahnrad mit gegebenen Parametern überhaupt erstellbar ist
    bool verifyAndLog(bool condition, string message);
    hpreal getShiftAngle(); //Winkel, um den Evolvente verschoben wird, damit auf dem Teilkreis gilt: Größe Zahnlücke = Größe Zahnbreite
    hpreal getStopFilletInvoluteAngle(); //Evolventenwinkel, an dem Fußrundung endet/in Evolvente übergeht
    hpreal getStartFilletAngle(); //Winkel, an dem Fußrundung startet
    hpreal involuteToCircleAngle(const hpreal &involuteAngle); //calculates the normal angle, one would expect in a cirle, out of the involute angle, which is used to construct the involute
    hpreal involuteAngleOfIntersectionWithCircle(const hpreal &radius);
    hpvec2 mirrorPoint(const hpvec2 &point, const hpvec2 &axis);

    hpvec2 pointOnRightTurnedInvolute(const hpreal &involuteStartAngle, const hpreal &angle);
    void insertCirclePoints(vector<hpvec2> &v, const hpuint &start, const hpuint &stopBefore,
                                            const hpreal &sampleAngleSize,
                                                const hpreal &radius);
    void insertFilletPoints(vector<hpvec2> &v, const hpuint &start, const hpuint &stopBefore,
                                                    const hpreal &sampleAngleSize,
                                                    const hpreal &angle);
    void insertInvolutePoints(vector<hpvec2> &v, const hpuint &start, const hpuint &stopBefore,
                                                    const hpreal &startInvAngle, const hpreal &stopInvAngle);
};

#endif // INVOLUTEGEAR_H
