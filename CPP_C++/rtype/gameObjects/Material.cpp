/*
** EPITECH PROJECT, 2020
** CPP_rtype
** File description:
** Material
*/

#include "Material.hpp"
#include "PointerHandler.hpp"

Material *Material::createMaterial(const std::string &filename)
{
	if (PointerHandler::materials.count(filename))
		return PointerHandler::materials.at(filename).get();
	std::unique_ptr<Material> m(new Material(filename));
	Material *ptr = m.get();
	PointerHandler::materials[filename] = std::move(m);
	return ptr;
}

Material::Material(const std::string& filename)
{
	_texture.loadFromFile(filename);
}

Material::~Material()
{
}