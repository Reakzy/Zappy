/*
** TimeUnit.hh for cpp_time in /home/werp/rendu/cpp_time/TimeUnit.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Tue Jun 27 14:43:24 2017 Paul Wéry
** Last update Tue Jun 27 14:43:24 2017 Paul Wéry
*/

#ifndef CPP_TIME_TIMEUNIT_HH
#define CPP_TIME_TIMEUNIT_HH

# include <cmath>
# include <chrono>
# include <map>

class TimeUnit
{
  long						refTime;
  bool						inProgress;
  unsigned int					frequency;
  std::map<std::string, unsigned int>		actionsTimeUnit;
  std::chrono::system_clock::time_point		startAnimation;
  std::chrono::system_clock::time_point		pastTimePoint;
  std::chrono::system_clock::time_point		currentTimePoint;
  long						endAnimation;

 public:

  void			setFrequency(unsigned int frequence);
  bool			startCheckTime(const std::string &action);
  long			elapsedTime();
  long			remainingTime();
  long			timeAction() const;

  TimeUnit();
  TimeUnit(const TimeUnit &) = delete;
  ~TimeUnit();
  TimeUnit	&operator=(const TimeUnit &) = delete;
};


#endif //CPP_TIME_TIMEUNIT_HH
