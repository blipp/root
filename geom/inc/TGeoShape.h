// @(#)root/geom:$Name:  $:$Id: TGeoShape.h,v 1.8 2003/02/07 13:46:47 brun Exp $
// Author: Andrei Gheata   31/01/02

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TGeoShape
#define ROOT_TGeoShape

#ifndef ROOT_TNamed
#include "TNamed.h"
#endif


// forward declarations
class TGeoParamCurve : public TObject
{
public:
   TGeoParamCurve() {;}
   virtual ~TGeoParamCurve() {}

   ClassDef(TGeoParamCurve, 1)
};

class TGeoBoolCombinator;
class TGeoMatrix;
class TGeoHMatrix;
class TGeoVolume;

/*************************************************************************
 * TGeoShape - base class for geometric shapes. Provides virtual methods
 *   for point and segment classification that has to be implemented by 
 *   all classes inheriting from it.
 *
 *************************************************************************/

class TGeoShape : public TNamed
{
public:
enum EShapeType {
   kGeoNoShape = 0,
   kGeoBad     = BIT(5),
   kGeoRSeg    = BIT(6),
   kGeoPhiSeg  = BIT(7),
   kGeoThetaSeg = BIT(8),
   kGeoVisX    = BIT(9),
   kGeoVisY    = BIT(10),
   kGeoVisZ    = BIT(11),
   kGeoRunTimeShape = BIT(12),
   kGeoInvalidShape = BIT(13),
   kGeoBox     = BIT(15),
   kGeoPara    = BIT(16),
   kGeoSph     = BIT(17),
   kGeoTube    = BIT(18),
   kGeoTubeSeg = BIT(19), 
   kGeoCone    = BIT(20),
   kGeoConeSeg = BIT(21),
   kGeoPcon    = BIT(22),
   kGeoPgon    = BIT(23),
   kGeoArb8    = BIT(24),
   kGeoEltu    = BIT(25),
   kGeoTrap    = BIT(26),
   kGeoCtub    = BIT(27),
   kGeoTrd1    = BIT(28),
   kGeoTrd2    = BIT(29),
   kGeoComb    = BIT(30)
};
static const Double_t kRadDeg;   // conversion factor rad->deg
static const Double_t kDegRad;   // conversion factor deg->rad
static const Double_t kBig;      // infinity
protected :
// data members
   Int_t                 fShapeId;   // shape id
// methods

public:
   // constructors
   TGeoShape();
   TGeoShape(const char *name);
   // destructor
   virtual ~TGeoShape();
   // methods

   static Double_t       ClosenessToCorner(Double_t *point, Bool_t in, Double_t *vertex,
                                           Double_t *normals, Double_t *cldir);
   virtual void          ComputeBBox()                           = 0;
   virtual Bool_t        Contains(Double_t *point) const         = 0;
   virtual Bool_t        CouldBeCrossed(Double_t *point, Double_t *dir) const = 0;
   virtual Int_t         DistancetoPrimitive(Int_t px, Int_t py) = 0;
   static Double_t       DistToCorner(Double_t *point, Double_t *dir, Bool_t in,
                                      Double_t *vertex, Double_t *norm, Int_t &inorm); 
   virtual Double_t      DistToOut(Double_t *point, Double_t *dir, Int_t iact=1, 
                                   Double_t step=0, Double_t *safe=0) const = 0;
   virtual Double_t      DistToIn(Double_t *point, Double_t *dir, Int_t iact=1, 
                                   Double_t step=0, Double_t *safe=0) const = 0;
   virtual Double_t      DistToSurf(Double_t *point, Double_t *dir) const = 0;
   virtual TGeoVolume   *Divide(TGeoVolume *voldiv, const char *divname, Int_t iaxis, Int_t ndiv, 
                                Double_t start, Double_t step)   = 0; 
   virtual const char   *GetAxisName(Int_t iaxis) const = 0;
   virtual Double_t      GetAxisRange(Int_t iaxis, Double_t &xlo, Double_t &xhi) const = 0;
   virtual void          GetBoundingCylinder(Double_t *param) const = 0;
   virtual Int_t         GetByteCount() const                          = 0;
   Int_t                 GetId() const  {return fShapeId;}
   virtual TGeoShape    *GetMakeRuntimeShape(TGeoShape *mother) const  = 0;
   virtual const char   *GetName() const;
   static Int_t          GetVertexNumber(Bool_t vx, Bool_t vy, Bool_t vz);
   virtual Bool_t        IsCylType() const = 0;
   Bool_t                IsRunTimeShape() const {return TestBit(kGeoRunTimeShape);}
   Bool_t                IsValid() const {return !TestBit(kGeoInvalidShape);}
   virtual Bool_t        IsValidBox() const                      = 0; 
   virtual void          InspectShape() const                    = 0;
   virtual void         *Make3DBuffer(const TGeoVolume *vol) const              = 0;
   virtual void          NextCrossing(TGeoParamCurve *c, Double_t *point) const = 0;
   virtual void          Paint(Option_t *option)                 = 0;
   virtual void          PaintNext(TGeoHMatrix *glmat, Option_t *option) = 0;
   virtual Double_t      Safety(Double_t *point, Bool_t in=kTRUE) const = 0;
   static  Double_t      SafetyPhi(Double_t *point, Bool_t in, Double_t c1, Double_t s1, Double_t c2, Double_t s2);
   virtual void          SetDimensions(Double_t *param)          = 0;
   void                  SetId(Int_t id) {fShapeId = id;}
   virtual void          SetPoints(Double_t *buff) const         = 0;
   virtual void          SetPoints(Float_t *buff) const          = 0;
   void                  SetRuntime(Bool_t flag=kTRUE) {SetBit(kGeoRunTimeShape, flag);}
   Int_t                 ShapeDistancetoPrimitive(Int_t numpoints, Int_t px, Int_t py) const;
   virtual void          Sizeof3D() const                        = 0;
   
  ClassDef(TGeoShape, 1)           // base class for shapes
};

#endif

