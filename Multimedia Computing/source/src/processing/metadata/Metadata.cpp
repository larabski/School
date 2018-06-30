//
//  Metadata.cpp
//  Project-CM
//
//  Created by Francisco Cunha on 04/05/2018.
//

#include "Metadata.hpp"

//--------------------------------------------------------------

Metadata::Metadata() {}

//--------------------------------------------------------------

Metadata::Metadata(string name, string sectionName) {
  this->name = name;
  this->sectionName = sectionName;
}

//--------------------------------------------------------------

void Metadata::setName(string name) {
  
  this->name = name;
}

//--------------------------------------------------------------

void Metadata::setDate(string date) {
  this->date = date;
}

//--------------------------------------------------------------

void Metadata::setColorR(string color) {
  this->colorR = color;
}

//--------------------------------------------------------------

void Metadata::setColorG(string color) {
  this->colorG = color;
}

//--------------------------------------------------------------

void Metadata::setColorB(string color) {
  this->colorB = color;
}

//--------------------------------------------------------------

void Metadata::setLuminance(string luminance) {
  this->luminance = luminance;
}

//--------------------------------------------------------------

void Metadata::setEdgeDistribution(string edgeDistribution) {
  this->edgeDistribution = edgeDistribution;
}

//--------------------------------------------------------------

void Metadata::setNumberFaces(string numberFaces) {
  this->numberFaces = numberFaces;
}

//--------------------------------------------------------------

void Metadata::setTexture(string texture) {
  this->texture = texture;
}

//--------------------------------------------------------------

void Metadata::setRythm(string rythm) {
  this->rythm = rythm;
}

//--------------------------------------------------------------

void Metadata::setSectionName(string sectionName) {
  this->sectionName = sectionName;
}

//--------------------------------------------------------------

string Metadata::getName() {
  return this->name;
}

//--------------------------------------------------------------

string Metadata::getDate() {
  return this->date;
}

//--------------------------------------------------------------

string Metadata::getColorR() {
  return this->colorR;
}

//--------------------------------------------------------------

string Metadata::getColorG() {
  return this->colorG;
}

//--------------------------------------------------------------

string Metadata::getColorB() {
  return this->colorB;
}

//--------------------------------------------------------------

string Metadata::getLuminance() {
  return this->luminance;
}

//--------------------------------------------------------------

string Metadata::getEdgeDistribution() {
  return this->edgeDistribution;
}

//--------------------------------------------------------------

string Metadata::getNumberFaces() {
  return this->numberFaces;
}

//--------------------------------------------------------------

string Metadata::getTexture() {
  return this->texture;
}

//--------------------------------------------------------------

string Metadata::getRythm() {
  return this->rythm;
}

//--------------------------------------------------------------

string Metadata::getSectionName() {
  return this->sectionName;
}

//--------------------------------------------------------------

void Metadata::logContent() {
  cout << "---------------------------------------------------" << endl
    << "[Name] --------- " << name << endl
    << "[Date] --------- " << date << endl
    << "[Luminance] ---- " << luminance << endl
    << "[RGB] ---------- " << colorR << " / " << colorG <<  " / " << colorB << endl
    << "[Edges] -------- " << edgeDistribution << endl
    << "[Faces] -------- " << numberFaces << endl
    << "[Texture] ------ " << texture << endl
    << "[Rythm] -------- " << rythm << endl
    << "---------------------------------------------------" << endl;
}
