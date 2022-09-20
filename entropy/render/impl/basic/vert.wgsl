struct CameraUniform {
    view_proj: mat4x4<f32>,
}
@group(0) @binding(0) var<uniform> camera: CameraUniform;

struct DrawPushConstants {
    model: mat4x4<f32>,
}
var<push_constant> draw: DrawPushConstants;

struct VertexInput {
    @location(0) position: vec3<f32>,
    @location(1) color: vec4<f32>,
    @location(2) uv: vec2<f32>,
}

struct VertexOutput {
    @builtin(position) clip_position: vec4<f32>,
    @location(0) color: vec4<f32>,
}

@vertex fn main(
    in: VertexInput,
) -> VertexOutput {
    var out: VertexOutput;
    var model_view_proj = draw.model * camera.view_proj;
    out.clip_position = vec4<f32>(in.position, 1.0) * model_view_proj;
    out.color = 0.5 * (vec4<f32>(in.position, 1.0) + vec4<f32>(1.0, 1.0, 1.0, 1.0));
    return out;
}
