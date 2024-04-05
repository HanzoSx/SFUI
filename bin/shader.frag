// Fragment shader
uniform vec2 mouse_position;

void main() {
    // 计算片段到鼠标位置的距离
    float distanceToMouse = distance(gl_FragCoord.xy, mouse_position);

    // 计算圆形的半径
    float radius = 50.0;

    // 如果片段在圆形内，则为白色，否则为透明
    if (distanceToMouse < radius) {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 0.6);  // 白色
    } else {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        // discard;  // 丢弃片段（透明）
    }
}
