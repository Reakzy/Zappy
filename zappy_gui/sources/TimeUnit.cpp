/*
** TimeUnit.cpp for cpp_time in /home/werp/rendu/cpp_time/TimeUnit.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Tue Jun 27 14:43:24 2017 Paul Wéry
** Last update Tue Jun 27 14:43:24 2017 Paul Wéry
*/

# include "TimeUnit.hh"

TimeUnit::TimeUnit()
{
  frequency = 1;
  inProgress = false;
  refTime = static_cast<long>(std::pow(10, 9));
  actionsTimeUnit["forward"] = 7;
  actionsTimeUnit["left"] = 7;
  actionsTimeUnit["right"] = 7;
  actionsTimeUnit["look"] = 7;
  actionsTimeUnit["inventory"] = 1;
  actionsTimeUnit["broadcast"] = 7;
  actionsTimeUnit["fork"] = 42;
  actionsTimeUnit["eject"] = 7;
  actionsTimeUnit["take object"] = 7;
  actionsTimeUnit["set object"] = 7;
  actionsTimeUnit["incantation"] = 300;
  actionsTimeUnit["open gate"] = actionsTimeUnit["forward"];
}

TimeUnit::~TimeUnit()
{

}

void TimeUnit::setFrequency(unsigned int frequency)
{
  this->frequency = frequency;
}

bool TimeUnit::startCheckTime(const std::string &action)
{
  unsigned int frequency = this->frequency;

  if (actionsTimeUnit.find(action) == actionsTimeUnit.end())
    return (false);
  inProgress = true;
  startAnimation = std::chrono::system_clock::now();
  endAnimation = startAnimation.time_since_epoch().count() + (refTime / frequency * actionsTimeUnit.find(action)->second);
  currentTimePoint = startAnimation;
  pastTimePoint = startAnimation;
  return (true);
}

long TimeUnit::elapsedTime()
{
  if (!inProgress)
    return (0);
  pastTimePoint = currentTimePoint;
  currentTimePoint = std::chrono::system_clock::now();
  if (currentTimePoint.time_since_epoch().count() > endAnimation)
    inProgress = false;
  return (currentTimePoint.time_since_epoch().count() - pastTimePoint.time_since_epoch().count());
}

long TimeUnit::remainingTime()
{
  if (!inProgress)
    return (0);
  currentTimePoint = std::chrono::system_clock::now();
  if (currentTimePoint.time_since_epoch().count() > endAnimation)
    {
      inProgress = false;
      return (0);
    }
  return (endAnimation - currentTimePoint.time_since_epoch().count());
}

long TimeUnit::timeAction() const
{
  if (!inProgress)
    return (0);
  return (endAnimation - startAnimation.time_since_epoch().count());
}