/*
** VolumeLight.hh for zappy_gui in /home/werp/rendu/zappy_gui/VolumeLight.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Wed Jun 28 15:34:18 2017 Paul Wéry
** Last update Wed Jun 28 15:34:18 2017 Paul Wéry
*/

#ifndef ZAPPY_GUI_VOLUMELIGHT_HH
#define ZAPPY_GUI_VOLUMELIGHT_HH

# include "irrlicht.h"
# include "ParserJson.hh"

class VolumeLight
{
  irr::scene::ISceneManager			*sceneManager;
  irr::video::IVideoDriver			*videoDriver;
  ParserJson					parserJson;
  irr::scene::IVolumeLightSceneNode		*volumeLight;
  irr::core::array<irr::video::ITexture*>	textures;
  irr::scene::ISceneNodeAnimator		*textureAnimator;
  unsigned int					speed;
  bool						used;
  std::string					keyBloc;

  bool		loadTextures(const std::string &animation);

 public:


  bool		&isUsed();
  std::string	&assignedBloc();
  void		loadVolumeLight(const std::string &fileConf, const std::string &animation);

  irr::scene::IVolumeLightSceneNode		*getVolumeLight();

  VolumeLight(irr::scene::ISceneManager *_sceneManager, irr::video::IVideoDriver *_videoDriver);
  VolumeLight(const VolumeLight &) = delete;
  ~VolumeLight();
  VolumeLight		&operator=(const VolumeLight &) = delete;
};


#endif //ZAPPY_GUI_VOLUMELIGHT_HH
