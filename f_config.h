
#ifndef F_CONFIG_H
#define F_CONFIG_H

/* Options for the file to be outputted. */
#define IMAGE_FILENAME "default_30M.ppm"
#define IMAGE_WIDTH    800
#define IMAGE_HEIGHT   800

/* Duration of time in seconds for progress to be printed. */
#define PROGRESS_PRINT_INTERVAL 3.0

/* Options for the numerical integration of the system. */
#define CIRCLE_SAMPLES 2000000
#define MAX_INTEGRATE_ITERATIONS 200000
#define CIRCLE_TO_PIXEL_TOLERANCE 0.3
#define DELTA_R 0.01
#define LAMBDA_STEP_MIN_IN 0
#define LAMBDA_STEP_MAX_IN 100
#define LAMBDA_STEP_MIN_OUT 0.0001
#define LAMBDA_STEP_MAX_OUT 5

/* Options for the scene to be rendered.
 * Note that the black hole is at z = 0.
 */
#define CAMERA_Z 100
#define CAMERA_HEIGHT 30
#define BARRIER_Z -10

/* Options for the background to be used.
 * Important! Only select the one from CHECKER_COLORS_ON or
 *            QUADRANT_COLORS_ON. If neither is selected, the
 *            default color is used.
 */
#define CHECKER_COLORS_ON 0
#define QUADRANT_COLORS_ON 0

/* Options to tweak the behavior of the static backgrounds. */
#define DEFAULT_COLOR_R 255
#define DEFAULT_COLOR_B 255
#define DEFAULT_COLOR_G 255

#define QUADRANT_COLOR_ONE_R 255
#define QUADRANT_COLOR_ONE_G 0
#define QUADRANT_COLOR_ONE_B 0
#define QUADRANT_COLOR_TWO_R 0
#define QUADRANT_COLOR_TWO_G 255
#define QUADRANT_COLOR_TWO_B 0
#define QUADRANT_COLOR_THREE_R 0
#define QUADRANT_COLOR_THREE_G 0
#define QUADRANT_COLOR_THREE_B 255
#define QUADRANT_COLOR_FOUR_R 255
#define QUADRANT_COLOR_FOUR_G 0
#define QUADRANT_COLOR_FOUR_B 255

#define CHECKER_WIDTH 2.0
#define CHECKER_HEIGHT 2.0
#define CHECKER_COLOR_ON_R 255
#define CHECKER_COLOR_ON_G 0
#define CHECKER_COLOR_ON_B 0
#define CHECKER_COLOR_OFF_R 0
#define CHECKER_COLOR_OFF_G 0
#define CHECKER_COLOR_OFF_B 255

#endif
