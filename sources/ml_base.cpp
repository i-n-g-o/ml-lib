/*
 * ml-lib, a machine learning library for Max and Pure Data
 * Copyright (C) 2013 Carnegie Mellon University
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ml_base.h"

#include <sstream>


namespace ml
{
    // Utility function declarations
    void post_prefixed_message(const std::string object_name, const std::string &message, void(*post_function)(const char *,...));

    // base implementation
    void base::post(const std::string &message) const
    {
        std::stringstream message_lines(message);
        std::string line;
        
        while(std::getline(message_lines, line, '\n'))
        {
            post_prefixed_message(get_object_name() + " " + ML_VERSION, line, flext::post);
        }
    }
    
    void base::error(const std::string &message) const
    {
        post_prefixed_message(get_object_name(), message, flext::error);
    }
    
    const std::string base::get_help_string(void) const
    {
        ml_doc::max_formatter formatter;
        ml_doc::doc_manager &doc_manager = ml_doc::doc_manager::shared_instance(formatter);
        std::string doc = doc_manager.doc_for_class(get_object_name());
        return doc;
    }
    
    // Utility function definitions
    void post_prefixed_message(const std::string object_name, const std::string &message, void(*post_function)(const char *,...))
    {
        std::string full_message = object_name + ": " + message;
        post_function(full_message.c_str());
    }
}
