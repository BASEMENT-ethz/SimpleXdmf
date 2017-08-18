# SimpleXdmf
A C++ header-only library to produce XDMF format file.
SimpleXdmf does not have complete functionalities for Xdmf, but does not require building with HDF5 (and Boost).

# Installation
Clone it into your project.
```bash
git clone https://github.com/hsimyu/SimpleXdmf.git
```
and copy a header file "simple_xdmf.hpp" to your include directory.

or, if your project already used cmake to build,
add the line below into your CMakeLists.txt.
```cmake
add_subdirectory(SimpleXdmf)
```

# How To Use
```cpp
#include <simple_xdmf.hpp>

int main() {
    SimpleXdmf gen;

    // Some settings
    gen.setNewLineCodeLF();

    const int nx = 5;
    const int ny = 3;

    gen.beginDomain();
    gen.setName("Domain1");
        gen.beginGrid();
        gen.setName("Grid1");
            gen.beginStructuredTopology("2DCoRectMesh");
            gen.setNumberOfElements(ny, nx);
            gen.setName("Topo1");
            gen.endStructuredTopology();

            gen.beginGeometory("ORIGIN_DXDY");
            gen.setDimensions(ny, nx);
            gen.setName("Geom1");
                // Origin
                gen.beginDataItem();
                    gen.setDimensions(2);
                    gen.setFormat("XML");
                    gen.addItem(0.0, 0.0);
                gen.endDataItem();

                gen.beginDataItem();
                    gen.setDimensions(2);
                    gen.setFormat("XML");
                    gen.addItem(0.5, 0.5);
                gen.endDataItem();
            gen.endGeometory();

            gen.beginAttribute();
            gen.setCenter("Node");
            gen.setName("Attr1");
                gen.beginDataItem();
                    gen.setDimensions(ny, nx);
                    gen.setFormat("XML");

                    // Adding from std::vector
                    std::vector<float> node_values;

                    for(int i = 0; i < (nx * ny); ++i) {
                        node_values.emplace_back(i);
                    }

                    gen.addVector(node_values);
                gen.endDataItem();
            gen.endAttribute();
        gen.endGrid();
    gen.endDomain();

    gen.generate("test.xmf");

    return 0;
}
```

This sample code generates
```xml
<?xml version="1.0" ?>
<!DOCTYPE Xdmf SYSTEM "Xdmf.dtd" []>
<Xdmf Version="3.0">
    <Domain Name="Domain1">
        <Grid GridType="Uniform">
            <Topology TopologyType="2DCoRectMesh" NumberOfElements="3 5" Name="Topo1"/>
            <Geometry GeometryType="ORIGIN_DXDY" Dimensions="3 5" Name="Geom1">
                <DataItem DataItemType="Uniform" Dimensions="2" Format="XML">
                    0 0 
                </DataItem>
                <DataItem DataItemType="Uniform" Dimensions="2" Format="XML">
                    0.5 0.5 
                </DataItem>
            </Geometry>
            <Attribute AttributeType="Scalar" Center="Node" Name="Attr1">
                <DataItem DataItemType="Uniform" Dimensions="3 5" Format="XML">
                    0 1 2 3 4 5 6 7 8 9 
                    10 11 12 13 14
                </DataItem>
            </Attribute>
        </Grid>
    </Domain>
</Xdmf>
```

See the examples in the examples directory.

# License
MIT
