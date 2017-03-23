#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

float circle(vec2 uv,vec2 p,float r)
{
	return r - (step(length(p - uv),1.));
}

float gear(vec2 uv,vec2 p,float r,float r2,float r3,float rotationSpeed,float RotationOffset)
{
	rotationSpeed = rotationSpeed * sin( time ) * 5.;
	
	uv = mod(uv,1.);
	float rad = length(p - uv);
	vec2 HolePos = (vec2(sin(  -rotationSpeed ),cos( -rotationSpeed )) * 0.12) - (abs(uv) - p);
	
	float SideHolesRad = length(  HolePos );
	
	float c = 1. - clamp(step(r - rad, 1.),0.,1.);
	float c2 = 1. - clamp(step((r + r2) - rad, 1.),0.,1.);
	float c3 = 1. - clamp(step((r - r3) - rad , 1. ) ,0.,1.);
	float c4 = 1. - clamp(1. - step( SideHolesRad , .05 ) ,0.,1.);
	
	
	vec2 n = normalize(p - uv);
		
	float radialUv = ((atan(  n.x , n.y ) ) + 1. * 0.5) ;
	
	
	radialUv += (mod(rotationSpeed,3.14) ) + RotationOffset;
	
	radialUv = clamp( (sin( radialUv * 10.  )),0.,1.) * 1.;
	float Gear =  ( max(c , radialUv ) * c2) - c3 - c4;
	//return c4;
	return clamp(Gear,0.,1.);	
}

void main( void )
{
	vec2 uv = ( gl_FragCoord.xy / resolution.xy ) + mouse / .50;
	uv.x *= resolution.x/resolution.y;
	uv -= .25;
	uv *= .95;
	
	uv += vec2(sin(time ),0.) * 1.;
	vec3 c = gear(uv,vec2(0.5,0.5),1.21,0.04,0.07,1.,0.) * (1. - (cos(time * 1.3) * 0.017)) * vec3(mod(0.3,0.4),0.5,0.4);	
	uv += vec2(0.5,0.);
	c = max(gear(uv,vec2(0.5,0.5),1.23,0.04,0.2,-1.,0.25) * (1. - (cos(time * 2.3) * 0.5)) * vec3(0.4,mod(0.4,0.5),0.5),c);
	uv += vec2(0.,0.5);
	c = max(gear(uv,vec2(0.5,0.5),1.21,0.0425,0.09,1.,0.) * (1. - (cos(time * 3.3) * 0.61)) * vec3(0.4,0.4,mod(0.5,0.6)),c);
	uv += vec2(0.5,0.);
	c = max(gear(uv,vec2(0.5,0.5),1.23,0.045,0.06,-1.,0.25) * (1. - (cos(time * 4.13) * 0.93)) * vec3(mod(0.4,0.5),0.5,0.6),c);
	
	vec3 o = vec3(0.2,mod(0.1,0.3),0.2);
	o = mix(o,c,0.5);
	
	gl_FragColor = vec4( o, 1.0 );
}