// Copyright (C) 2004, 2010 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

#ifndef __IPRESTOC_1NRM_HPP__
#define __IPRESTOC_1NRM_HPP__

#include "IpRestoPhase.hpp"
#include "IpIpoptAlg.hpp"
#include "IpEqMultCalculator.hpp"

namespace Ipopt
{

/** Restoration Phase that minimizes the 1-norm of the constraint
 *  violation - using the interior point method (Ipopt).
 */
class MinC_1NrmRestorationPhase: public RestorationPhase
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor, taking strategy objects.
    *
    *  The resto_alg strategy object is the restoration phase Ipopt
    *  algorithm.  The eq_mult_calculator is used to reinitialize the
    *  equality constraint multipliers after the restoration phase
    *  algorithm has finished - unless it is NULL, in which case the
    *  multipliers are set to 0.
    */
   MinC_1NrmRestorationPhase(
      IpoptAlgorithm&                         resto_alg,
      const SmartPtr<EqMultiplierCalculator>& eq_mult_calculator
   );

   /** Destructor */
   virtual ~MinC_1NrmRestorationPhase();
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );

protected:
   virtual bool PerformRestoration();

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    *
    * These methods are not implemented
    * and we do not want the compiler to implement them for us, so we
    * declare them private and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Default Constructor */
   MinC_1NrmRestorationPhase();

   /** Copy Constructor */
   MinC_1NrmRestorationPhase(
      const MinC_1NrmRestorationPhase&
   );

   /** Default Assignment Operator */
   void operator=(
      const MinC_1NrmRestorationPhase&
   );
   ///@}

   /** @name Strategy objects */
   ///@{
   SmartPtr<IpoptAlgorithm> resto_alg_;
   SmartPtr<EqMultiplierCalculator> eq_mult_calculator_;
   ///@}

   /** Copy of original options, which is required to initialize the
    *  Ipopt algorithm strategy object before restoration phase is
    *  started.
    */
   SmartPtr<OptionsList> resto_options_;

   /** @name Algorithmic parameters */
   ///@{
   Number constr_mult_reset_threshold_;

   /** Maximal allowed value of a bound multiplier after restoration
    *  phase.
    */
   Number bound_mult_reset_threshold_;

   /** Indicates whether problem can be expected to be infeasible.
    *
    *  This will request the to set kappa_resto to a small value for
    *  the first time the restoration phase is called.  (ToDo)
    */
   bool expect_infeasible_problem_;

   /** Constraint violation tolerance */
   Number constr_viol_tol_;

   /** Primal infeasibility tolerance for declaring failure of
    *  restoration phase when the non-regular termination tests are
    *  met.
    */
   Number resto_failure_feasibility_threshold_;
   ///@}

   /** Counter for the number of time that PerformRestoration is
    *  called.
    */
   Index count_restorations_;

   /** @name Auxiliary methods */
   ///@{
   /** Method for computing "primal-dual" step in bound multipliers,
    *  given step in slacks.
    */
   void ComputeBoundMultiplierStep(
      Vector&       delta_z,
      const Vector& curr_z,
      const Vector& curr_slack,
      const Vector& trial_slack
   );
   ///@}
};

} // namespace Ipopt

#endif
