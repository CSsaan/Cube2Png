# from pylut import *
# lut = LUT.FromCubeFile("/EA_Cinematic_Lut1.cube")

# # print lut.ColorAtLatticePoint(1,2,1)
# # print lut.ColorAtInterpolatedLatticePoint(1.3,1.5,1.2)
# # print lut.ColorFromColor(Color(.002,.5,.2344))
# # print lut.ColorFromColor(Color.FromRGBInteger(14, 1000, 30, bitdepth = 10))

# lut = lut.Resize(64)
# lut.ToNuke3DLFile("/EA_Cinematic_Lut64.cube")



from pylut import pylut

lut = pylut.LUT.FromCubeFile("EA_Cinematic_Lut1.cube")
# lut2 = LUT.FromLustre3DLFile("/path/to/file2.3dl")

# lut3 = lut.CombineWithLUT(lut2)

# lut3 *= .5
# lut3 -= LUT.FromIdentity(lut3.cubeSize)

# lut3 = lut3.ClampColor(Color(0,0,.2),Color(0,0,.4))

lut = lut.Resize(64)
lut.ToCubeFile("EA_Cinematic_Lut64.cube")