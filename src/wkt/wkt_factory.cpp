/*****************************************************************************
 * 
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2011 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

// boost
#include <boost/version.hpp>

// mapnik
#include <mapnik/wkt/wkt_factory.hpp>
#include <mapnik/wkt/wkt_grammar.hpp>

// stl
#include <string>
#include <sstream>

namespace mapnik
{

bool from_wkt(std::string const& wkt, boost::ptr_vector<geometry_type> & paths)
{
#if BOOST_VERSION >= 104700
    using namespace boost::spirit;
    typedef std::string::const_iterator iterator_type;
    iterator_type first = wkt.begin();
    iterator_type last =  wkt.end();
    mapnik::wkt::wkt_collection_grammar<iterator_type> grammar;
    return qi::phrase_parse(first, last, grammar, ascii::space, paths);
#else
    // TODO - remove this after mapnik 2.0.0 release
    std::ostringstream s;
    s << BOOST_VERSION/100000 << "." << BOOST_VERSION/100 % 1000  << "." << BOOST_VERSION % 100;
    throw std::runtime_error("mapnik::from_wkt() requires at least boost 1.47 while your build was compiled against boost " + s.str());
    return false;
#endif
}

}

