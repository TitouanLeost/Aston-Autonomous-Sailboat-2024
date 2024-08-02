#include <Algorithms.h>

/*=======================================================*/
/*==================== LineFollowing ====================*/
/*=======================================================*/

LineFollowing::LineFollowing() {}


LineFollowing::~LineFollowing() {}


void LineFollowing::updateCmd()
{
    CoordXY m = m_obs->gps()->getCoordXY();

    float x = m.x;
    float y = m.y;

    Serial.println("x: " + String(x) + " y: " + String(y));

    float theta = (float)(((int)(-m_obs->cmps()->getYaw() + 90 + 360))%360) * M_PI/180;
    float angle_truewind = (float)(((int)(-m_obs->getTrueWindAngle() - 90 + 720))%360) * M_PI/180;

    Serial.println("theta: " + String(theta*180/M_PI) + " angle_truewind: " + String(angle_truewind*180/M_PI));

    float dx = m_b.x - m_a.x;
    float dy = m_b.y - m_a.y;
    float N = sqrt(dx*dx + dy*dy);

    Serial.println("dx: " + String(dx) + " dy: " + String(dy) + " N: " + String(N));

    float e = (dx*(y - m_a.y) - dy*(x - m_a.x))/N;

    Serial.println("e: " + String(e));

    if(abs(e) > R/2) {
        m_q = e/abs(e);

        Serial.println("m_q: " + String(m_q));
    }
    
    float angle_target = atan2(dy, dx);
    float angle_nominal = angle_target - 2*GAMMA*atan(e/R)/M_PI;
    float angle_actual = angle_nominal;

    Serial.println("angle_target: " + String(angle_target*180/M_PI) + " angle_nominal: " + String(angle_nominal*180/M_PI) + " angle_actual: " + String(angle_actual*180/M_PI));

    if((cos(angle_truewind - angle_nominal) + cos(ZETA) < 0) or (abs(e) < R and cos(angle_truewind - angle_target) + cos(ZETA) < 0)) {
        angle_actual = pi + angle_truewind - m_q*ZETA;

        Serial.println("m_q: " + String(m_q));
        Serial.println("angle_actual (if): " + String(angle_actual*180/M_PI));
    }

    float angle_rudder = ANGLE_RUDDER_MAX/M_PI * sawtooth(theta - angle_actual);
    float angle_sail = M_PI/2 * pow(((cos(angle_truewind - angle_actual) + 1)/2), (log(M_PI/(2*BETA)) / log(2)));

    Serial.println("angle_rudder: " + String(angle_rudder*180/M_PI) + " angle_sail: " + String(angle_sail*180/M_PI));

    m_cmd_rudder = 1 - (angle_rudder + ANGLE_RUDDER_MAX) / (2*ANGLE_RUDDER_MAX);
    m_cmd_sail = angle_sail / (ANGLE_SAIL_MAX);

    Serial.println("m_cmd_rudder: " + String(m_cmd_rudder) + " m_cmd_sail: " + String(m_cmd_sail));
    Serial.println("==============================================\n");
}


void LineFollowing::updateWaypoint(CoordLatLon a, CoordLatLon b)
{
    LineFollowing::setLine(a, b);
}


void LineFollowing::setLine(CoordLatLon a, CoordLatLon b)
{
    m_a = latLonToXY(a);
    m_b = latLonToXY(b);
}


/*=======================================================*/
/*==================== SationKeeping ====================*/
/*=======================================================*/

StationKeeping::StationKeeping(){}


StationKeeping::~StationKeeping(){}


void StationKeeping::updateCmd()
{
    m_cmd_rudder = 0.6;
    m_cmd_sail = 0.4;
}

