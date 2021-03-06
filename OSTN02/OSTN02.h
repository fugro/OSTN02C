//
//  OSTN02.h
//  OSTN02
//
//  Created by George MacKerron on 24/12/2011.
//  Copyright (c) 2011 George MacKerron. All rights reserved.
//

#ifndef OSTN02_OSTN02_h
#define OSTN02_OSTN02_h

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#ifdef USE_LONG
#define DBL       long double
#else
#define DBL       double
#endif

#ifdef DONT_PACK
#define PACKED
#else
#define PACKED    __attribute__((packed))
#endif

typedef struct {
  int num;
  int emin;
  int nmin;
  int emax;
  int nmax;
  char nameUTF8[77];
  char sheetUTF8[46];
} OSMap;

typedef struct {
  int deg;  // usual range 0 - 180 (S or W)
  int min;  // usual range 0 - 60
  DBL sec;
  bool westOrSouth;
} DegMinSec;

typedef struct {
  DBL e;
  DBL n;
  DBL elevation;
  unsigned char geoid;
} EastingNorthing;

typedef struct {
  char letters[2];
  int e;
  int n;
  int resolution;  // 1/10/100/1000m
} GridRefComponents;

typedef struct {
  DBL lat;
  DBL lon;
  DBL elevation;
  unsigned char geoid;
} LatLonDecimal;

typedef struct {
  DegMinSec lat;
  DegMinSec lon;
  DBL elevation;
  unsigned char geoid;
} LatLonDegMinSec;

typedef struct {
  DBL semiMajorAxis;
  DBL semiMinorAxis;
} Ellipsoid;

typedef struct {
  DBL centralMeridianScale;
  LatLonDecimal trueOriginLatLon;
  EastingNorthing trueOriginEastingNorthing;
} MapProjection;

typedef struct {
  unsigned int eMin   : 10;
  unsigned int eCount : 10;
  unsigned int offset : 20;
} PACKED OSTN02Index;

typedef struct {
  unsigned int eShift : 15;
  unsigned int nShift : 15;
  unsigned int gShift : 14;
  unsigned int gFlag  :  4;
} PACKED OSTN02Datum;

DBL gridConvergenceDegreesFromLatLon(const LatLonDecimal latLon, const Ellipsoid ellipsoid, const MapProjection projection);
DBL gridConvergenceDegreesFromEastingNorthing(const EastingNorthing en, const Ellipsoid ellipsoid, const MapProjection projection);
DBL gridConvergenceDegreesFromOSGB36EastingNorthing(const EastingNorthing en);
DBL gridConvergenceDegreesFromETRS89LatLon(const LatLonDecimal latLon);
int nextOSExplorerMap(EastingNorthing en, int prevMap);
EastingNorthing   eastingNorthingFromLatLon(const LatLonDecimal latLon, const Ellipsoid ellipsoid, const MapProjection projection);
EastingNorthing   ETRS89EastingNorthingFromETRS89LatLon(const LatLonDecimal latLon);
LatLonDecimal     latLonFromEastingNorthing(const EastingNorthing en, const Ellipsoid ellipsoid, const MapProjection projection);
LatLonDecimal     ETRS89LatLonFromETRS89EastingNorthing(const EastingNorthing en);
EastingNorthing   OSTN02ShiftsForIndices(const int eIndex, const int nIndex);
EastingNorthing   shiftsForEastingNorthing(const EastingNorthing en);
EastingNorthing   OSGB36EastingNorthingFromETRS89EastingNorthing(const EastingNorthing en);
EastingNorthing   ETRS89EastingNorthingFromOSGB36EastingNorthing(const EastingNorthing en);
DegMinSec         degMinSecFromDecimal(DBL dec);
DBL               decimalFromDegMinSec(DegMinSec dms);
LatLonDegMinSec   latLonDegMinSecFromLatLonDecimal(const LatLonDecimal dec);
LatLonDecimal     latLonDecimalFromLatLonDegMinSec(const LatLonDegMinSec dms);
GridRefComponents gridRefComponentsFromOSGB36EastingNorthing(const EastingNorthing en, const int res);
char*             gridRefFromGridRefComponents(const GridRefComponents grc, const bool spaces);  // be sure to free(result) after use
char*             gridRefFromOSGB36EastingNorthing(const EastingNorthing en, const int res, const bool spaces);  // be sure to free(result) after use
char*             tetradFromOSGB36EastingNorthing(const EastingNorthing en);  // be sure to free(result) after use
bool              test(const bool noisily);

#endif
