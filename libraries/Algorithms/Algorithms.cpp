#include <Algorithms.h>


LineFollowing::LineFollowing(){}


LineFollowing::~LineFollowing(){}


void LineFollowing::setLine(CoordLatLon a, CoordLatLon b)
{
    m_a = latLonToXY(a);
    m_b = latLonToXY(b);
}


void LineFollowing::updateCmd()
{
    CoordXY m = m_obs->gps()->getCoordXY();

    float x = m.x;
    float y = m.y;

    float theta = m_obs->cmps()->getYaw() * M_PI/180;
    float angle_truewind = m_obs->getTrueWindAngle() * M_PI/180;

    float dx = m_b.x - m_a.x;
    float dy = m_b.y - m_a.y;
    float N = sqrt(dx*dx + dy*dy);

    float e = (dx*(y - m_a.y) - dy*(x - m_a.x))/N;

    if(abs(e) > R/2)
        m_q = e/abs(e);
    
    float angle_target = atan2(dy, dx);
    float angle_nominal = angle_target - 2*GAMMA*atan(e/R)/M_PI;
    float angle_actual = angle_nominal;

    if((cos(angle_truewind - angle_nominal) + cos(ZETA) < 0) or (abs(e) < R and cos(angle_truewind - angle_target) + cos(ZETA) < 0))
        angle_actual = -angle_truewind - m_q*ZETA;

    float angle_rudder = ANGLE_RUDDER_MAX/M_PI * sawtooth(theta - angle_actual);
    float angle_sail = M_PI/2 * pow(((cos(angle_truewind - angle_actual) + 1)/2), (log(M_PI/(2*BETA)) / log(2)));

    m_cmd_rudder = 1 - (angle_rudder + ANGLE_RUDDER_MAX) / (2*ANGLE_RUDDER_MAX);
    m_cmd_sail = (angle_sail + ANGLE_SAIL_MAX) / (2*ANGLE_SAIL_MAX);
}