
#include <string> 
#include "open3d/Open3D.h"
#include "open3d/t/geometry/RaycastingScene.h"
#include <Open3D/t/geometry/Geometry.h>
#include <Open3D/t/geometry/TriangleMesh.h>
#include <Open3D/t/io/TriangleMeshIO.h>

int main(int argc, char *argv[]) {
    //base stl file
    const std::string STL_BASE = "D:/work/open3d-cmake-find-package/Benchy.stl";
    const std::string STL_BASE_SUPPORT = "D:/work/open3d-cmake-find-package/Benchy SUPPORT.stl";

    open3d::t::geometry::TriangleMesh mesh;
    open3d::t::geometry::TriangleMesh pillars_mesh;
    open3d::t::geometry::TriangleMesh result_mesh;
    
    if (!open3d::t::io::ReadTriangleMesh(STL_BASE, mesh)) {
        printf("Failed to load subject mesh.\n");
        return -1;
    }

    if (!open3d::t::io::ReadTriangleMesh(STL_BASE_SUPPORT, pillars_mesh)) {
        printf("Failed to load merged pillars mesh.\n");
        return -1;
    }
       
    // Create a RaycastingScene
    open3d::t::geometry::RaycastingScene scene;
    
    // Access vertex positions and triangle indices
    open3d::core::Tensor vertex_positions = mesh.GetVertexPositions();
    open3d::core::Tensor triangle_indices = mesh.GetTriangleIndices();

    // Correct the data type to UInt32 if needed
    if (vertex_positions.GetDtype() != open3d::core::Dtype::Float32) {
        vertex_positions = vertex_positions.To(open3d::core::Dtype::Float32);
    }

    if (triangle_indices.GetDtype() != open3d::core::Dtype::UInt32) {
        triangle_indices = triangle_indices.To(open3d::core::Dtype::UInt32);
    }

    // Add the triangles to the scene
    uint32_t scene_id = scene.AddTriangles(vertex_positions, triangle_indices);

     std::shared_ptr<open3d::geometry::Geometry> geoptr = 
             std::make_shared<open3d::geometry::TriangleMesh>(mesh.ToLegacy());
   
    open3d::visualization::Visualizer visualizer;
    open3d::visualization::RenderOption renderOptions;
    visualizer.CreateVisualizerWindow("Open3D Visualizer",1280, 720);
    visualizer.AddGeometry(geoptr);
    visualizer.GetRenderOption().point_size_ = renderOptions.POINT_SIZE_MAX;
    visualizer.Run();
    return 0;
   
}
