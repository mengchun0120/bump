#ifdef GL_ES
precision mediump float;
#endif

uniform bool useColor;
uniform vec4 color;
uniform sampler2D texture;

varying vec2 texCoord;

void main() {
    if(useColor) {
        gl_FragColor = color;
    } else {
        gl_FragColor = texture2D(texture, texCoord);
    }
}
