# How Matrixes Allow Interactive Rendering of Block Meshes


## Chunks and Model Matrix (Local Space to World Space)


### Starting Block Positions (Chunk Space or Local Space)
$Block Positions = \begin{bmatrix}\begin{pmatrix}x_{b1},&y_{b1},&z_{b1}\end{pmatrix}\ldots\end{bmatrix}$ (Relative to Chunk Origin)


### Chunk Wide Logic to Convert to World Space
$CL = Chunk Location = \begin{pmatrix}x_c,&y_c\end{pmatrix} * Chunk Size$ (Relative to World Origin)\
$ModelMat4 = \begin{bmatrix}1&0&0&CL.x\cr0&1&0&CL.y\cr0&0&1&CL.z\cr0&0&0&1\end{bmatrix}$ (Chunk to World Space Transformation Matrix)


## Camera and View Matrix (World Space to View Space)

### Camera State
$CamP = CameraPosition = \begin{pmatrix}x_{cam},&y_{cam},&z_{cam}\end{pmatrix}$ (World Space)\
$CamR = CameraRotation = \begin{pmatrix}pitch,&yaw\end{pmatrix}$ (Rotation Without Roll)\
```const``` $CU = Camera Up Vector = \begin{pmatrix}0,&1,&0\end{pmatrix}$ (World Up Direction [which is constant])


### View Matrix Components

$VT = Translation = \begin{bmatrix}1&0&0&-CamP.x\cr0&1&0&-CamP.y\cr0&0&1&-CamP.z\cr0&0&0&1\end{bmatrix}$ (Location Relative to Camera Transformation Matrix)


#### Camera Front Direction

$CFX = Camera Front Vector X = cos(CamR.{yaw}) * cos(CamR.{pitch})$\
$CFY = Camera Front Vector Y = sin(CamR.{pitch})$\
$CFZ = Camera Front Vector Z = sin(CamR.{yaw}) * cos(CamR.{pitch})$\
$CF = Camera Front Vector = ||\left<VFX, VFY, VFZ\right>||$ (Normalized Look / Front Vector)

$CR = Camera Right Vector = ||CU \times CF||$ (Right Direction is the Normalized Cross Product of Up and Front Directions)

#### Adding in Camera Rotation

$VR = Rotation = \begin{bmatrix}CR.x&CR.y&CR.z&0\cr CU.x&CU.y&CU.z&0\cr CF.x&CF.y&CF.z&o\cr0&0&0&1\end{bmatrix}$ (Rotation Relative to Camera Transformation Matrix)

$ViewMat4 = VR * VT = \begin{bmatrix}CR.x&CR.y&CR.z&0\cr CU.x&CU.y&CU.z&0\cr CF.x&CF.y&CF.z&0\cr0&0&0&1\end{bmatrix} * \begin{bmatrix}1&0&0&-CamP.x\cr0&1&0&-CamP.y\cr0&0&1&-CamP.z\cr0&0&0&1\end{bmatrix} = \begin{bmatrix}CR.x&CR.y&CR.z&0\cr CU.x&CU.y&CU.z&0\cr CF.x&CF.y&CF.z&0\cr0&0&0&1\end{bmatrix}$\
 (World Space to View Space Transformation Matrix [the Coordinate Space Relative to the Camera])

## Putting all Together in a Vertex Shader

Inputs:*\
```in``` $ModelMat4$\
```in``` $ViewMat4$\
```const``` $ProjectionMat4$

```in vec3``` $BlockPositions$

Outputs:*\
$Vertices = (ProjectionMat4 * ViewMat4 * ModelMat4 * $``` vec4```$\left<BlockPositions, 0\right>).xyz$\
$ = (ProjectionMat4 * \begin{bmatrix}CR.x&CR.y&CR.z&0\cr CU.x&CU.y&CU.z&0\cr CF.x&CF.y&CF.z&0\cr0&0&0&1\end{bmatrix} * \begin{bmatrix}1&0&0&-CamP.x\cr0&1&0&-CamP.y\cr0&0&1&-CamP.z\cr0&0&0&1\end{bmatrix} * \begin{bmatrix}1&0&0&CL.x\cr0&1&0&CL.y\cr0&0&1&CL.z\cr0&0&0&1\end{bmatrix} * $``` vec4```$\left<BlockPositions, 0\right>).xyz$\
(Pad the block location into a 4D vector for rotation, apply transformations, and truncate to 3D vector)

*(Additional Inputs and Outputs Are Used for Texture and Normal Vector Lookups for Blocks)


## Use Case
By applying these transformations we are able to store vertex locations for the blocks in the world in chunk space allowing them to not lose accuracy for floating point vertex locations and use less bytes for integer ones. Additionally, by utilizing the view and projection matrixes, we are able to move the camera around the scene, look around, and zoom in and out by changing the FOV of the projection frustum (the 3D shape projected from the camera in which vertices are rendered). This allows for a more interactive experience by laying the foundation of the player controller system.