#include <simple_xdmf.hpp>

int main() {
    SimpleXdmf gen;

    gen.beginDomain();
        gen.beginTopology();
            gen.beginDataItem();
            gen.endDataItem();
        gen.endTopology();
        gen.beginGeometory();
            gen.beginDataItem();
            gen.endDataItem();
        gen.endGeometory();
    gen.endDomain();

    gen.generate("test.xmf");

    return 0;
}