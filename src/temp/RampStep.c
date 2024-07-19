// max speed in mm / min
/**
 * 
 */

/**
 * Steps per rotation:
 * - 200 for 1.8 deg full step
 * - 400 for 0.9 deg full step
 * (TODO - move to config)
 */
#define STEPS_PER_ROTATION = 200

/**
 * Radius to calculate linear shift acc. to step
 *               <--
 *    _________|_____|_______
 *   /     \
 *  |   o---|  <--- SHAFT_RADIUS
 *   \_____/_________________
 */
#define SHAFT_RADIUS = 100 // in mm

#define ELO = STEPS_PER_ROTATION / SHAFT_RADIUS

unsigned long getLon() {
  return 10;
}

