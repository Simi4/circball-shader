import QtQuick 2.9
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import com.meshes 1.0

Entity {
    Entity {
        components: [
            SphereMesh {
                primitiveType: GeometryRenderer.Lines
                slices: 64
                rings: 64
            },
            OverlayMaterial {
                //
            }
        ]
    }

    Entity {
        components: [
            CircBallMesh {
                //
            },
            CircBallMaterial {
                //
            }
        ]
    }
}
