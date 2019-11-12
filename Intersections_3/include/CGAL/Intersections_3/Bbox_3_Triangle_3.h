// Copyright (c) 2010 GeometryFactory (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL$
// $Id$
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Sebastien Loriot
//

#ifndef CGAL_INTERSECTIONS_3_BBOX_3_TRIANGLE_3_H
#define CGAL_INTERSECTIONS_3_BBOX_3_TRIANGLE_3_H

#include <CGAL/Bbox_3.h>
#include <CGAL/Triangle_3.h>

#include <CGAL/Intersections_3/internal/Bbox_3_Triangle_3_do_intersect.h>

namespace CGAL {

template<typename K>
bool do_intersect(const CGAL::Bbox_3& a,
                  const Triangle_3<K>& b) {
  return K().do_intersect_3_object()(a, b);
}

template<typename K>
bool do_intersect(const Triangle_3<K>& a,
                  const CGAL::Bbox_3& b) {
  return K().do_intersect_3_object()(a, b);
}


} // namespace CGAL

#endif // CGAL_INTERSECTIONS_3_BBOX_3_TRIANGLE_3_H
