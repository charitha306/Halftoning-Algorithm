/**\file */
#ifndef SLIC_DECLARATIONS_Simple_H
#define SLIC_DECLARATIONS_Simple_H
#include "MaxSLiCInterface.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define Simple_PCIE_ALIGNMENT (16)


/*----------------------------------------------------------------------------*/
/*---------------------------- Interface default -----------------------------*/
/*----------------------------------------------------------------------------*/




/**
 * \brief Basic static function for the interface 'default'.
 * 
 * \param [in] param_N Interface Parameter "N".: Number of data items to process
 * \param [in] inscalar_SimpleKernel_cols Input scalar parameter "SimpleKernel.cols".
 * \param [in] inscalar_SimpleKernel_one Input scalar parameter "SimpleKernel.one".
 * \param [in] inscalar_SimpleKernel_rows Input scalar parameter "SimpleKernel.rows".
 * \param [in] inscalar_SimpleKernel_threshold Input scalar parameter "SimpleKernel.threshold".
 * \param [in] inscalar_SimpleKernel_zero Input scalar parameter "SimpleKernel.zero".
 * \param [in] instream_eg The stream should be of size (param_N * 4) bytes.
 * \param [in] instream_ep The stream should be of size (param_N * 4) bytes.
 * \param [in] instream_in_image The stream should be of size (param_N * 2) bytes.
 * \param [out] outstream_out_image The stream should be of size (param_N * 2) bytes.
 */
void Simple(
	int32_t param_N,
	uint64_t inscalar_SimpleKernel_cols,
	uint64_t inscalar_SimpleKernel_one,
	uint64_t inscalar_SimpleKernel_rows,
	uint64_t inscalar_SimpleKernel_threshold,
	uint64_t inscalar_SimpleKernel_zero,
	const float *instream_eg,
	const float *instream_ep,
	const int16_t *instream_in_image,
	int16_t *outstream_out_image);

/**
 * \brief Basic static non-blocking function for the interface 'default'.
 * 
 * Schedule to run on an engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 * 
 * 
 * \param [in] param_N Interface Parameter "N".: Number of data items to process
 * \param [in] inscalar_SimpleKernel_cols Input scalar parameter "SimpleKernel.cols".
 * \param [in] inscalar_SimpleKernel_one Input scalar parameter "SimpleKernel.one".
 * \param [in] inscalar_SimpleKernel_rows Input scalar parameter "SimpleKernel.rows".
 * \param [in] inscalar_SimpleKernel_threshold Input scalar parameter "SimpleKernel.threshold".
 * \param [in] inscalar_SimpleKernel_zero Input scalar parameter "SimpleKernel.zero".
 * \param [in] instream_eg The stream should be of size (param_N * 4) bytes.
 * \param [in] instream_ep The stream should be of size (param_N * 4) bytes.
 * \param [in] instream_in_image The stream should be of size (param_N * 2) bytes.
 * \param [out] outstream_out_image The stream should be of size (param_N * 2) bytes.
 * \return A handle on the execution status, or NULL in case of error.
 */
max_run_t *Simple_nonblock(
	int32_t param_N,
	uint64_t inscalar_SimpleKernel_cols,
	uint64_t inscalar_SimpleKernel_one,
	uint64_t inscalar_SimpleKernel_rows,
	uint64_t inscalar_SimpleKernel_threshold,
	uint64_t inscalar_SimpleKernel_zero,
	const float *instream_eg,
	const float *instream_ep,
	const int16_t *instream_in_image,
	int16_t *outstream_out_image);

/**
 * \brief Advanced static interface, structure for the engine interface 'default'
 * 
 */
typedef struct { 
	int32_t param_N; /**<  [in] Interface Parameter "N".: Number of data items to process */
	uint64_t inscalar_SimpleKernel_cols; /**<  [in] Input scalar parameter "SimpleKernel.cols". */
	uint64_t inscalar_SimpleKernel_one; /**<  [in] Input scalar parameter "SimpleKernel.one". */
	uint64_t inscalar_SimpleKernel_rows; /**<  [in] Input scalar parameter "SimpleKernel.rows". */
	uint64_t inscalar_SimpleKernel_threshold; /**<  [in] Input scalar parameter "SimpleKernel.threshold". */
	uint64_t inscalar_SimpleKernel_zero; /**<  [in] Input scalar parameter "SimpleKernel.zero". */
	const float *instream_eg; /**<  [in] The stream should be of size (param_N * 4) bytes. */
	const float *instream_ep; /**<  [in] The stream should be of size (param_N * 4) bytes. */
	const int16_t *instream_in_image; /**<  [in] The stream should be of size (param_N * 2) bytes. */
	int16_t *outstream_out_image; /**<  [out] The stream should be of size (param_N * 2) bytes. */
} Simple_actions_t;

/**
 * \brief Advanced static function for the interface 'default'.
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in,out] interface_actions Actions to be executed.
 */
void Simple_run(
	max_engine_t *engine,
	Simple_actions_t *interface_actions);

/**
 * \brief Advanced static non-blocking function for the interface 'default'.
 *
 * Schedule the actions to run on the engine and return immediately.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * 
 * \param [in] engine The engine on which the actions will be executed.
 * \param [in] interface_actions Actions to be executed.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simple_run_nonblock(
	max_engine_t *engine,
	Simple_actions_t *interface_actions);

/**
 * \brief Group run advanced static function for the interface 'default'.
 * 
 * \param [in] group Group to use.
 * \param [in,out] interface_actions Actions to run.
 *
 * Run the actions on the first device available in the group.
 */
void Simple_run_group(max_group_t *group, Simple_actions_t *interface_actions);

/**
 * \brief Group run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule the actions to run on the first device available in the group and return immediately.
 * The status of the run must be checked with ::max_wait. 
 * Note that use of ::max_nowait is prohibited with non-blocking running on groups:
 * see the ::max_run_group_nonblock documentation for more explanation.
 *
 * \param [in] group Group to use.
 * \param [in] interface_actions Actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simple_run_group_nonblock(max_group_t *group, Simple_actions_t *interface_actions);

/**
 * \brief Array run advanced static function for the interface 'default'.
 * 
 * \param [in] engarray The array of devices to use.
 * \param [in,out] interface_actions The array of actions to run.
 *
 * Run the array of actions on the array of engines.  The length of interface_actions
 * must match the size of engarray.
 */
void Simple_run_array(max_engarray_t *engarray, Simple_actions_t *interface_actions[]);

/**
 * \brief Array run advanced static non-blocking function for the interface 'default'.
 * 
 *
 * Schedule to run the array of actions on the array of engines, and return immediately.
 * The length of interface_actions must match the size of engarray.
 * The status of the run can be checked either by ::max_wait or ::max_nowait;
 * note that one of these *must* be called, so that associated memory can be released.
 *
 * \param [in] engarray The array of devices to use.
 * \param [in] interface_actions The array of actions to run.
 * \return A handle on the execution status of the actions, or NULL in case of error.
 */
max_run_t *Simple_run_array_nonblock(max_engarray_t *engarray, Simple_actions_t *interface_actions[]);

/**
 * \brief Converts a static-interface action struct into a dynamic-interface max_actions_t struct.
 *
 * Note that this is an internal utility function used by other functions in the static interface.
 *
 * \param [in] maxfile The maxfile to use.
 * \param [in] interface_actions The interface-specific actions to run.
 * \return The dynamic-interface actions to run, or NULL in case of error.
 */
max_actions_t* Simple_convert(max_file_t *maxfile, Simple_actions_t *interface_actions);

/**
 * \brief Initialise a maxfile.
 */
max_file_t* Simple_init(void);

/* Error handling functions */
int Simple_has_errors(void);
const char* Simple_get_errors(void);
void Simple_clear_errors(void);
/* Free statically allocated maxfile data */
void Simple_free(void);
/* returns: -1 = error running command; 0 = no error reported */
int Simple_simulator_start(void);
/* returns: -1 = error running command; 0 = no error reported */
int Simple_simulator_stop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* SLIC_DECLARATIONS_Simple_H */

