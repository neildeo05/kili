v0: Was intended to be like a Google TPU -> inherent architecture (lack of keeping the weights stationary) makes it impractical to follow the same architecutre
v1 (pivot): More along the lines of a GPGPU/Snitch Cluster

## Core Architecture

TMatMul does a (8,8) * (8,1) -> (8,1) matrix vector product. 