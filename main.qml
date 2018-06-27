import QtQuick 2.9
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0


Entity {
    id: sceneRoot

    Camera {
        id: cameraRoot
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: _window.width / _window.height
        nearPlane: 0.1
        farPlane: 1000.0
        position: Qt.vector3d(0.014, 0.956, 2.178)
        upVector: Qt.vector3d(0.0, 1.0, 0.0)
        viewCenter: Qt.vector3d(0.0, 0.0, 0.0)
    }

    OrbitCameraController {
        camera: cameraRoot
        linearSpeed: 50.0
        lookSpeed: 180.0
    }

    CircBall { }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                clearColor: Qt.rgba(0.5, 0.5, 0.5, 1)
                camera: cameraRoot
            }
        },

        InputSettings { }
    ]
}
