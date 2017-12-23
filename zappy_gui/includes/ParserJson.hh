/*
** ParserJson.hh for cpp_indie_studio in /home/werp/rendu/cpp_indie_studio/ParserJson.hh
**
** Made by Paul Wéry
** Login   <paul.wery@epitech.eu>
**
** Started on  Wed May 24 15:56:33 2017 Paul Wéry
** Last update Wed May 24 15:56:33 2017 Paul Wéry
*/

#ifndef CPP_INDIE_STUDIO_PARSERJSON_HH
#define CPP_INDIE_STUDIO_PARSERJSON_HH

#include <map>
#include <regex>
#include <vector>
#include <fstream>
#include <iostream>

class		ParserJson
{
  std::regex						regexContent;
  std::regex						regexLabel;
  std::regex						regexBloc;
  std::regex						regexLine;
  std::regex						regexKeyValue;
  std::regex						regexTab;
  bool							success;
  std::string						pathFile;

 public:

  struct valuesKeyString
  {
    std::map<std::string, std::string>			stringValues;
    std::map<std::string, double>			numericValues;
    std::map<std::string, std::vector<std::string>>	stringTabValues;
    std::map<std::string, std::vector<double>>		numericTabValues;
  };

  typedef std::shared_ptr<struct valuesKeyString> Data;

 private:

  Data						bloc;
  std::shared_ptr<std::map<std::string, Data>>	blocsString;

  bool		getBufferFile(std::string &buffer, const std::string &pathFile) const;
  void		parseAttributs(const std::string &bloc);
  void		parseLine(const std::string &line);
  void		parseTab(const std::string &key, const std::string &tab);
  void		fullStruct(const std::string &key, const std::string &value);
  std::string	rmQuote(const std::string &str) const;

 public:

  bool		loadFile(const std::string &pathFile);

  std::shared_ptr<std::map<std::string, Data>>	getBlocsString() const;
  Data						getBlocString(const std::string &key) const;


  ParserJson();
  ~ParserJson();
  ParserJson(const ParserJson &obj) = delete;
  ParserJson &operator=(const ParserJson &obj) = delete;
};

#endif //CPP_INDIE_STUDIO_PARSERJSON_HH
