/*
** MeshLoader.hh for zappy_gui in /home/werp/rendu/zappy_gui/MeshLoader.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Wed Jun 21 14:45:14 2017 Paul Wéry
// Last update Thu Jun 22 22:44:25 2017 Wéry
*/

#ifndef ZAPPY_GUI_MESHLOADER_HH
#define ZAPPY_GUI_MESHLOADER_HH

# include <string>
# include "irrlicht.h"
# include "ParserJson.hh"

class MeshLoader
{

  ParserJson			parserJson;
  irr::scene::ISceneManager	*scene;
  irr::video::IVideoDriver	*driver;
  unsigned int			frequency;

  irr::scene::IAnimatedMeshSceneNode	*loadMesh(ParserJson::Data bloc) const;

  bool		isValidNode(irr::scene::IAnimatedMeshSceneNode *node, ParserJson::Data bloc) const;
  bool		loadTexture(irr::scene::IAnimatedMeshSceneNode *node, ParserJson::Data bloc) const;
  bool		loadPosRot(irr::scene::IAnimatedMeshSceneNode *node, ParserJson::Data bloc) const;
  bool		loadScale(irr::scene::IAnimatedMeshSceneNode *node, ParserJson::Data bloc) const;

 public:

  void					setFrequency(unsigned int frequency);
  irr::scene::IAnimatedMeshSceneNode	*loadAsset(const std::string &asset, const std::string &fileName);

  MeshLoader(irr::scene::ISceneManager *_scene, irr::video::IVideoDriver *_driver);
  MeshLoader(const MeshLoader &) = delete;
  ~MeshLoader();
  MeshLoader	&operator=(const MeshLoader &) = delete;
};


#endif //ZAPPY_GUI_MESHLOADER_HH
