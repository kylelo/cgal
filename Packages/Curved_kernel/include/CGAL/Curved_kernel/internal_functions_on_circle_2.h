// Copyright (c) 2005  INRIA Sophia-Antipolis (France) 
// All rights reserved.
//
// Authors : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//           Sylvain Pion     <Sylvain.Pion@sophia.inria.fr>
// 
// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_CURVED_KERNEL_INTERNAL_FUNCTIONS_ON_CIRCLE_2_H
#define CGAL_CURVED_KERNEL_INTERNAL_FUNCTIONS_ON_CIRCLE_2_H

#include <CGAL/global_functions_on_roots_and_polynomials_2_2.h>

CGAL_BEGIN_NAMESPACE

// temporary function : where to put it, if we want to keep it ?
template< class CK>
typename CK::Circular_arc_point_2
circle_intersect( const typename CK::Circle_2 & c1,
		  const typename CK::Circle_2 & c2,
		  bool b )
{
  typedef std::vector<CGAL::Object > solutions_container;
  
  solutions_container solutions;
  CGAL::intersect_2<CK>( c1, c2, std::back_inserter(solutions) );
  
  typename solutions_container::iterator it = solutions.begin();
  
  CGAL_kernel_precondition( it != solutions.end() ); 
  // the circles intersect
  
  const std::pair<typename CK::Circular_arc_point_2, uint> *result;
  result = CGAL::object_cast< 
    std::pair<typename CK::Circular_arc_point_2, uint> >(&(*it));
  
  if ( result->second == 2 ) // double solution
    return result->first;
  
  if (b) 
    return result->first;
  
  ++it;
  result = CGAL::object_cast< 
    std::pair<typename CK::Circular_arc_point_2, uint> >(&(*it));
  return result->first;
}

namespace CircularFunctors {

  template < class CK >
  typename CK::Polynomial_for_circles_2_2
  get_equation( const typename CK::Circle_2 & c )
  {
    typedef typename CK::RT RT;
 
    typedef typename CK::Algebraic_kernel   AK;

    return AK().construct_polynomial_for_circles_2_2_object()
      ( c.center().x(), c.center().y(), c.squared_radius() );
  }
  
  template < class CK >
  typename CK::Circle_2  
  construct_circle_2( const typename CK::Polynomial_for_circles_2_2 &eq )
  {
    return typename CK::Circle_2( typename CK::Point_2(eq.a(), eq.b()), eq.r_sq() ); 
  }

  template< class CK, class OutputIterator>
  OutputIterator
  intersect_2( const typename CK::Circle_2 & c1,
	       const typename CK::Circle_2 & c2,
	       OutputIterator res )
  {
    typedef typename CK::Algebraic_kernel            AK;
    typedef typename CK::Polynomial_for_circles_2_2  Equation; 
    typedef typename CK::Root_for_circles_2_2        Root_for_circles_2_2;
    Equation e1 = get_equation<CK>(c1);
    Equation e2 = get_equation<CK>(c2);
    
    if (e1 == e2) {
      *res++ = make_object(e1);
      return res;
    }

    typedef std::vector< std::pair < Root_for_circles_2_2, unsigned > > 
      solutions_container;
    solutions_container solutions;

    AK().solve_object()(e1, e2, std::back_inserter(solutions)); // to be optimized

    typedef typename CK::Circular_arc_point_2 Circular_arc_point_2;
    
    for ( typename solutions_container::iterator it = solutions.begin(); 
	  it != solutions.end(); ++it )
      {
        *res++ = make_object(std::make_pair(Circular_arc_point_2(it->first),
			                      it->second ));
      }

    return res;
  }

  // Should we have an iterator based interface, or both ?
  template <class CK>
  typename CK::Circular_arc_point_2
  x_extremal_point(const typename CK::Circle_2 & c, bool i)
  {
    typedef typename CK::Algebraic_kernel   AK;
    return AK().x_critical_points_object()(typename CK::Get_equation()(c),i);
  }

  template <class CK,class OutputIterator>
  OutputIterator
  x_extremal_points(const typename CK::Circle_2 & c, OutputIterator res)
  {
    typedef typename CK::Algebraic_kernel   AK;
    return AK().x_critical_points_object()(typename CK::Get_equation()(c),res);
  }

  template <class CK>
  typename CK::Circular_arc_point_2
  y_extremal_point(const typename CK::Circle_2 & c, bool i)
  {
    typedef typename CK::Algebraic_kernel   AK;
    return AK().y_critical_points_object()(typename CK::Get_equation()(c),i);
  }
  
  template <class CK,class OutputIterator>
  OutputIterator
  y_extremal_points(const typename CK::Circle_2 & c, OutputIterator res)
  {
    typedef typename CK::Algebraic_kernel   AK;
    return AK().y_critical_points_object()(typename CK::Get_equation()(c),res);
  }


} // namespace CircularFunctors

CGAL_END_NAMESPACE

#endif // CGAL_CURVED_KERNEL_INTERNAL_FUNCTIONS_ON_CIRCLE_2_H
