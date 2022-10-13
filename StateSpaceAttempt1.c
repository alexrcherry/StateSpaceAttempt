/*
 * StateSpaceAttempt1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "StateSpaceAttempt1".
 *
 * Model version              : 1.2
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Thu Oct 13 13:35:26 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "StateSpaceAttempt1.h"
#include "StateSpaceAttempt1_private.h"

/* Block signals (default storage) */
B_StateSpaceAttempt1_T StateSpaceAttempt1_B;

/* Continuous states */
X_StateSpaceAttempt1_T StateSpaceAttempt1_X;

/* Real-time model */
static RT_MODEL_StateSpaceAttempt1_T StateSpaceAttempt1_M_;
RT_MODEL_StateSpaceAttempt1_T *const StateSpaceAttempt1_M =
  &StateSpaceAttempt1_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  StateSpaceAttempt1_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  StateSpaceAttempt1_step();
  StateSpaceAttempt1_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  StateSpaceAttempt1_step();
  StateSpaceAttempt1_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void StateSpaceAttempt1_step(void)
{
  real_T Sum_tmp;
  real_T rtb_Gain6;
  int32_T tmp;
  if (rtmIsMajorTimeStep(StateSpaceAttempt1_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&StateSpaceAttempt1_M->solverInfo,
                          ((StateSpaceAttempt1_M->Timing.clockTick0+1)*
      StateSpaceAttempt1_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(StateSpaceAttempt1_M)) {
    StateSpaceAttempt1_M->Timing.t[0] = rtsiGetT
      (&StateSpaceAttempt1_M->solverInfo);
  }

  /* Step: '<Root>/Step' incorporates:
   *  Step: '<Root>/Step1'
   *  Step: '<Root>/Step2'
   */
  Sum_tmp = StateSpaceAttempt1_M->Timing.t[0];

  /* Sum: '<Root>/Sum' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Integrator: '<Root>/Integrator'
   *  Step: '<Root>/Step'
   */
  StateSpaceAttempt1_B.Sum[0] = (0.0 * StateSpaceAttempt1_X.Integrator_CSTATE[1]
    + StateSpaceAttempt1_X.Integrator_CSTATE[0]) + (real_T)!(Sum_tmp < 0.0);
  StateSpaceAttempt1_B.Sum[1] = 2.0 * StateSpaceAttempt1_X.Integrator_CSTATE[0]
    + 0.0 * StateSpaceAttempt1_X.Integrator_CSTATE[1];

  /* Step: '<Root>/Step2' */
  if (Sum_tmp < 0.0) {
    tmp = 0;
  } else {
    tmp = 2;
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/Gain10'
   *  Gain: '<Root>/Gain11'
   *  Integrator: '<Root>/Integrator2'
   */
  rtb_Gain6 = 31.622776601683842 * (real_T)tmp - (12.291195968839395 *
    StateSpaceAttempt1_X.Integrator2_CSTATE[0] + 31.622776601683842 *
    StateSpaceAttempt1_X.Integrator2_CSTATE[1]);

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<Root>/Gain7'
   *  Gain: '<Root>/Gain8'
   *  Integrator: '<Root>/Integrator2'
   */
  StateSpaceAttempt1_B.Sum3[0] = (0.0 * StateSpaceAttempt1_X.Integrator2_CSTATE
    [1] + StateSpaceAttempt1_X.Integrator2_CSTATE[0]) + rtb_Gain6;
  StateSpaceAttempt1_B.Sum3[1] = (2.0 * StateSpaceAttempt1_X.Integrator2_CSTATE
    [0] + 0.0 * StateSpaceAttempt1_X.Integrator2_CSTATE[1]) + 0.0 * rtb_Gain6;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<Root>/Gain6'
   *  Integrator: '<Root>/Integrator1'
   *  Step: '<Root>/Step1'
   */
  rtb_Gain6 = (real_T)!(Sum_tmp < 0.0) - (12.291195968839395 *
    StateSpaceAttempt1_X.Integrator1_CSTATE[0] + 31.622776601683842 *
    StateSpaceAttempt1_X.Integrator1_CSTATE[1]);

  /* Sum: '<Root>/Sum1' incorporates:
   *  Gain: '<Root>/Gain3'
   *  Gain: '<Root>/Gain4'
   *  Integrator: '<Root>/Integrator1'
   */
  StateSpaceAttempt1_B.Sum1[0] = (0.0 * StateSpaceAttempt1_X.Integrator1_CSTATE
    [1] + StateSpaceAttempt1_X.Integrator1_CSTATE[0]) + rtb_Gain6;
  StateSpaceAttempt1_B.Sum1[1] = (2.0 * StateSpaceAttempt1_X.Integrator1_CSTATE
    [0] + 0.0 * StateSpaceAttempt1_X.Integrator1_CSTATE[1]) + 0.0 * rtb_Gain6;
  if (rtmIsMajorTimeStep(StateSpaceAttempt1_M)) {
    rt_ertODEUpdateContinuousStates(&StateSpaceAttempt1_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++StateSpaceAttempt1_M->Timing.clockTick0;
    StateSpaceAttempt1_M->Timing.t[0] = rtsiGetSolverStopTime
      (&StateSpaceAttempt1_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.04s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.04, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      StateSpaceAttempt1_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void StateSpaceAttempt1_derivatives(void)
{
  XDot_StateSpaceAttempt1_T *_rtXdot;
  _rtXdot = ((XDot_StateSpaceAttempt1_T *) StateSpaceAttempt1_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = StateSpaceAttempt1_B.Sum[0];

  /* Derivatives for Integrator: '<Root>/Integrator2' */
  _rtXdot->Integrator2_CSTATE[0] = StateSpaceAttempt1_B.Sum3[0];

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[0] = StateSpaceAttempt1_B.Sum1[0];

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE[1] = StateSpaceAttempt1_B.Sum[1];

  /* Derivatives for Integrator: '<Root>/Integrator2' */
  _rtXdot->Integrator2_CSTATE[1] = StateSpaceAttempt1_B.Sum3[1];

  /* Derivatives for Integrator: '<Root>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[1] = StateSpaceAttempt1_B.Sum1[1];
}

/* Model initialize function */
void StateSpaceAttempt1_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)StateSpaceAttempt1_M, 0,
                sizeof(RT_MODEL_StateSpaceAttempt1_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&StateSpaceAttempt1_M->solverInfo,
                          &StateSpaceAttempt1_M->Timing.simTimeStep);
    rtsiSetTPtr(&StateSpaceAttempt1_M->solverInfo, &rtmGetTPtr
                (StateSpaceAttempt1_M));
    rtsiSetStepSizePtr(&StateSpaceAttempt1_M->solverInfo,
                       &StateSpaceAttempt1_M->Timing.stepSize0);
    rtsiSetdXPtr(&StateSpaceAttempt1_M->solverInfo,
                 &StateSpaceAttempt1_M->derivs);
    rtsiSetContStatesPtr(&StateSpaceAttempt1_M->solverInfo, (real_T **)
                         &StateSpaceAttempt1_M->contStates);
    rtsiSetNumContStatesPtr(&StateSpaceAttempt1_M->solverInfo,
      &StateSpaceAttempt1_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&StateSpaceAttempt1_M->solverInfo,
      &StateSpaceAttempt1_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&StateSpaceAttempt1_M->solverInfo,
      &StateSpaceAttempt1_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&StateSpaceAttempt1_M->solverInfo,
      &StateSpaceAttempt1_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&StateSpaceAttempt1_M->solverInfo, (&rtmGetErrorStatus
      (StateSpaceAttempt1_M)));
    rtsiSetRTModelPtr(&StateSpaceAttempt1_M->solverInfo, StateSpaceAttempt1_M);
  }

  rtsiSetSimTimeStep(&StateSpaceAttempt1_M->solverInfo, MAJOR_TIME_STEP);
  StateSpaceAttempt1_M->intgData.y = StateSpaceAttempt1_M->odeY;
  StateSpaceAttempt1_M->intgData.f[0] = StateSpaceAttempt1_M->odeF[0];
  StateSpaceAttempt1_M->intgData.f[1] = StateSpaceAttempt1_M->odeF[1];
  StateSpaceAttempt1_M->intgData.f[2] = StateSpaceAttempt1_M->odeF[2];
  StateSpaceAttempt1_M->contStates = ((X_StateSpaceAttempt1_T *)
    &StateSpaceAttempt1_X);
  rtsiSetSolverData(&StateSpaceAttempt1_M->solverInfo, (void *)
                    &StateSpaceAttempt1_M->intgData);
  rtsiSetSolverName(&StateSpaceAttempt1_M->solverInfo,"ode3");
  rtmSetTPtr(StateSpaceAttempt1_M, &StateSpaceAttempt1_M->Timing.tArray[0]);
  StateSpaceAttempt1_M->Timing.stepSize0 = 0.04;

  /* block I/O */
  (void) memset(((void *) &StateSpaceAttempt1_B), 0,
                sizeof(B_StateSpaceAttempt1_T));

  /* states (continuous) */
  {
    (void) memset((void *)&StateSpaceAttempt1_X, 0,
                  sizeof(X_StateSpaceAttempt1_T));
  }

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  StateSpaceAttempt1_X.Integrator_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator2' */
  StateSpaceAttempt1_X.Integrator2_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  StateSpaceAttempt1_X.Integrator1_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  StateSpaceAttempt1_X.Integrator_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator2' */
  StateSpaceAttempt1_X.Integrator2_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<Root>/Integrator1' */
  StateSpaceAttempt1_X.Integrator1_CSTATE[1] = 0.0;
}

/* Model terminate function */
void StateSpaceAttempt1_terminate(void)
{
  /* (no terminate code required) */
}
