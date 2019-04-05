// ---------------------------------------------------------------------
//
// Copyright (C) 2019 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------

#ifndef dealii_differentiation_sd_symengine_types_h
#define dealii_differentiation_sd_symengine_types_h

#include <deal.II/base/config.h>

#ifdef DEAL_II_WITH_SYMENGINE

#  include <map>
#  include <vector>

DEAL_II_NAMESPACE_OPEN

namespace Differentiation
{
  namespace SD
  {
    // Forward declarations
    class Expression;


    namespace types
    {
      namespace internal
      {
        /**
         * A comparator for Expressions used as keys in maps.
         */
        struct ExpressionKeyLess
        {
          bool
          operator()(const SD::Expression &lhs,
                     const SD::Expression &rhs) const;
        };
      } // namespace internal

      /**
       * Type definition for a value substitution map.
       *
       * This serves the same purpose as a
       * <code>SymEngine::map_basic_basic</code>, which is equivalent to a
       * <code>std::map<SE::RCP<const SE::Basic>,  SE::RCP<const
       * SE::Basic>></code>.
       */
      using substitution_map =
        std::map<SD::Expression, SD::Expression, internal::ExpressionKeyLess>;

      /**
       * Type definition for a vector of symbols.
       *
       * This serves the same purpose as a <code>SymEngine::vec_basic</code>,
       * which is equivalent to a <code>std::vector<SE::RCP<const
       * SE::Basic>></code>
       */
      using symbol_vector = std::vector<SD::Expression>;

    } // namespace types

  } // namespace SD
} // namespace Differentiation


DEAL_II_NAMESPACE_CLOSE

#endif // DEAL_II_WITH_SYMENGINE

#endif // dealii_differentiation_sd_symengine_types_h
