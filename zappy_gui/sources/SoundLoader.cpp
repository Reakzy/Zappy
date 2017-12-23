/*
** SoundLoader.cpp for zappy_gui in /home/werp/rendu/zappy_gui/SoundLoader.cpp
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Wed Jun 21 14:45:24 2017 Paul Wéry
** Last update Wed Jun 21 14:45:24 2017 Paul Wéry
*/

#include "SoundLoader.hh"

SoundLoader::SoundLoader()
{
  this->engine = irrklang::createIrrKlangDevice();
  this->soundPlayed = nullptr;
}

SoundLoader::~SoundLoader()
{

}

void SoundLoader::playSound(const std::string &sound)
{
  if (this->engine != nullptr)
    this->soundPlayed = this->engine->play2D(sound.c_str());
}

void SoundLoader::playMusic(const std::string &music)
{
  if (this->engine != nullptr)
    this->soundPlayed = this->engine->play2D(music.c_str(), true, false, true);
}

void SoundLoader::loadSounds(const std::vector<std::string> &sounds)
{
  this->sounds = sounds;
}

void SoundLoader::playRandomMusicsLoaded()
{
  long		random = std::chrono::system_clock::now().time_since_epoch().count();

  if (this->engine == nullptr || sounds.size() == 0)
    return ;
  if (soundPlayed != nullptr)
    soundPlayed->stop();
  playMusic(sounds.at(random % sounds.size()));
}

void SoundLoader::playRandomSoundsLoaded()
{
  long		random = std::chrono::system_clock::now().time_since_epoch().count();

  if (this->engine == nullptr || sounds.size() == 0)
    return ;
  if (soundPlayed != nullptr)
    soundPlayed->stop();
  playSound(sounds.at(random % sounds.size()));
}

void SoundLoader::stopMusic()
{
  if (soundPlayed != nullptr)
    {
      soundPlayed->stop();
    }
}
