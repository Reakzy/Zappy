/*
** SoundLoader.hh for zappy_gui in /home/werp/rendu/zappy_gui/SoundLoader.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Wed Jun 21 14:45:24 2017 Paul Wéry
** Last update Wed Jun 21 14:45:24 2017 Paul Wéry
*/

#ifndef ZAPPY_GUI_SOUNDLOADER_HH
# define ZAPPY_GUI_SOUNDLOADER_HH

# include <irrKlang.h>
# include <vector>
# include <string>
# include <chrono>

class SoundLoader
{
  irrklang::ISoundEngine 	*engine;
  std::string			path;
  std::vector<std::string>	sounds;
  irrklang::ISound		*soundPlayed;


 public:

  void				stopMusic();

  void				playSound(const std::string &sound);
  void				playMusic(const std::string &music);

  void				playRandomMusicsLoaded();
  void				playRandomSoundsLoaded();
  void				loadSounds(const std::vector<std::string> &sounds);

  SoundLoader();
  SoundLoader(const SoundLoader& other) = delete;
  SoundLoader& operator=(const SoundLoader& other) = delete;

  ~SoundLoader();
};


#endif //ZAPPY_GUI_SOUNDLOADER_HH
