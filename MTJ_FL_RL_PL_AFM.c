//  Whole structure have 8 layers,FL: 4 layers,MgO 1 layers, RL 1 layer,Ru 1 layer,PL 1 layer
//  the shape is circle ,for diameter is D=100 nm

sizeX := 20e-9
sizeY := 20e-9
sizeZ := 20e-9
sizeP := 20e-9
Nx := 6
Ny := 6
Nz := 8
setcellsize(sizeX/Nx,sizeY/Ny,sizeZ/Nz)
SetGridsize(Nx,Ny, Nz)



FL := layer(7).Intersect(circle(sizeP))  //From No.5 layer to No.7 layer set as FLs
//setgeom(FL)
DefRegion(7,FL)
Msat.SetRegion(7, 1070e3)
Ku1.setregion(7, 1.070e3)
anisU.setRegion(7, vector(1, 0, 0))
m.SetRegion(7, uniform(1,0,0))
Aex.SetRegion(7,0.88e-11)
alpha.SetRegion(7,0.02)

RL := layer(6).Intersect(circle(sizeP))
//setgeom(RL)
DefRegion(6,RL)
Msat.SetRegion(6,1070e3)
Ku1.setregion(6, 1.07e3)
anisU.setRegion(6, vector(1, 0, 0))
m.SetRegion(6, uniform(1,0,0))
Aex.SetRegion(6,0.88e-11)
alpha.SetRegion(6,0.02)

//ext_scaleExchange(6, 7, 0.16e-2)
ext_scaleExchange(6, 7, 0.16e-2)




PL := layer(5).Intersect(circle(sizeP))
//setgeom(PL)
DefRegion(5,PL)
Msat.SetRegion(5,1140e3)
Ku1.setregion(5, 1.14e3)
anisU.setRegion(5, vector(1, 0, 0))
m.SetRegion(5, uniform(1,0,0))
Aex.SetRegion(5,1.0e-11)
alpha.SetRegion(5,0.02)

//ext_scaleExchange(5, 6, -1.54e-2)
ext_scaleExchange(5, 6, -1.54e-2)

AFM := layers(0,5)
DefRegion(0,AFM)
Msat.SetRegion(0,0e0)
Aex.SetRegion(0,0e-9)
m.SetRegion(0, uniform(1,0,0))
frozenspins.setRegion(0, 1) 


//ext_scaleExchange(0, 5, 0.34e-1 )
    
ext_scaleExchange(0,5,1.0e-2)

setgeom(PL.add(RL).add(FL).add(AFM))

//setgeom(AFM.add(PL))

EdgeSmooth = 8

relax()

//B_PL:= 5000
Bmax := 600e-3
//Bmin := -2500.0e-3
Bstep := 20.0e-3
MinimizerStop = 1e-6
TableAdd(B_ext)

TableAdd(m.Comp(0).region(0) )
//TableAdd(B_ext.region(5))
TableAdd(m.Comp(0).region(5))
//TableAdd(B_ext.region(5))
TableAdd(m.Comp(0).region(6))

TableAdd(m.Comp(0).region(7))
//TableAdd(m.region(1))

//B_ext.setRegion(0,vector(-B_PL,0,0))

for B:=0.0; B<=Bmax; B+=Bstep{
    B_ext = vector(B, 0, 0)
	/*
	B_ext.setRegion(5, vector(B, 0, 0))
	B_ext.setRegion(6, vector(B, 0, 0))
	B_ext.setRegion(7, vector(B, 0, 0))*/
    minimize()   // small changes best minimized by minimize()
    tablesave()
	save(m)
}

for B:=Bmax; B>=-Bmax; B-=Bstep{
    B_ext = vector(B, 0, 0)
	/*
    B_ext.setRegion(5, vector(B, 0, 0))
	B_ext.setRegion(6, vector(B, 0, 0))
	B_ext.setRegion(7, vector(B, 0, 0))*/
	minimize()   // small changes best minimized by minimize()
    tablesave()
	save(m)
}

for B:= -Bmax; B<=Bmax; B+=Bstep{
    B_ext = vector(B, 0, 0)
	/*
    B_ext.setRegion(5, vector(B, 0, 0))
	B_ext.setRegion(6, vector(B, 0, 0))
	B_ext.setRegion(7, vector(B, 0, 0))*/
	minimize()   // small changes best minimized by minimize()
    tablesave()
	save(m)
}
