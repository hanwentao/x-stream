/*
 * X-Stream
 *
 * Copyright 2013 Operating Systems Laboratory EPFL
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Until boost::log becomes mainstream use this substitute
#ifndef _BOOST_LOG_WRAPPER_
#define _BOOST_LOG_WRAPPER_
#include<iostream>
#include<string>
#include<sstream>
#include<boost/thread.hpp>
enum log_state {
  fatal = 0,
  error = 1,
  warn = 2,
  info = 3,
  total = 4
};

static const char *log_headers[total] = 
{"FATAL", 
 "ERROR",
 "WARNING",
 "INFO"};

class BOOST_LOG_TRIVIAL {
  enum log_state level;
 public:
  std::stringstream state;
  BOOST_LOG_TRIVIAL(enum log_state level_in)
    :level(level_in)
  {
  }
  template<typename T>
  BOOST_LOG_TRIVIAL& operator<< (T value)
  {
    state << value;
    return *this;
  }
  
  ~BOOST_LOG_TRIVIAL()
  {
    std::stringstream final;
    final << "<" << log_headers[level] << " ";
    final << boost::this_thread::get_id() << "> ";
    final << state.str() << std::endl;
    std::cerr << final.str();
    if(level == fatal) {
      BOOST_ASSERT_MSG(false, "Fatal stop.");
    }
  }
};

#endif
