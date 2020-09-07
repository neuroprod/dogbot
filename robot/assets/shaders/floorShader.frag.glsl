#version 150 core
uniform float alpha;
uniform float spec;
uniform sampler2DShadow uShadowMap;

in vec4 vColor;
in vec4 vPosition;
in vec4 vLight;
in vec3 vNormal;
in vec4 vShadowCoord;
in vec2 vUV;
uniform vec3 uViewPos;

out vec4 Color;

float samplePCF4x4( vec4 sc )
{
	const int r = 1;
	const int s = 2 * r;
	
	float shadow = 0.0;
	shadow += textureProjOffset( uShadowMap,  sc, ivec2(-s,-s) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2(-r,-s) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2( r,-s) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2( s,-s) );
	
	shadow += textureProjOffset( uShadowMap,  sc, ivec2(-s,-r) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2(-r,-r) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2( r,-r) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2( s,-r) );
	
	shadow += textureProjOffset( uShadowMap,  sc, ivec2(-s, r) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2(-r, r) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2( r, r) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2( s, r) );
	
	shadow += textureProjOffset( uShadowMap,  sc, ivec2(-s, s) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2(-r, s) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2( r, s) );
	shadow += textureProjOffset( uShadowMap,  sc, ivec2( s, s) );
		
	return shadow/16.0;
}



void main( void )
{
//todo fix+ make nice shading
	vec3 normal			= normalize( vNormal );

	vec3 lightDir		= normalize( vLight.xyz - vPosition.xyz );

	vec3 viewDir		= normalize( vPosition.xyz );
	float NdotL			=  dot( normal, lightDir);
	
	vec3 diffuse		= vec3( NdotL )*0.5 +0.5;
	vec3 Ambient		= vec3( 0.1 );
	
    vec3 viewDirR = normalize(uViewPos - vPosition.xyz);
    vec3 reflectDir = reflect(-lightDir, normal	);
    float spec = pow(max(dot(viewDirR, reflectDir), 0.0), 4)*spec;



	vec4 sc = vShadowCoord;
	vec4 ShadowCoord	= vShadowCoord / vShadowCoord.w;
	

	sc.z -= 0.005;
	float shadow = samplePCF4x4( sc );
	shadow =shadow*0.3+0.7;
    if(length(vPosition.xyz)>5000)
    {
        shadow =1.0;
    }

    vec2 uv=step(1.0,mod (vUV*100.0,2.0));
	float col =(uv.x +uv.y)*0.5 ;
	col =col *(1.0-(uv.x +uv.y)*0.5 );
	col=col +0.5;

  vec2 uv2=step(1.0,mod (vUV*1000.0,2.0));
	float col2 =(uv2.x +uv2.y)*0.5 ;
	col2 =col2 *(1.0-(uv2.x +uv2.y)*0.5 );
	col2=col2 +0.5;

    col+=col2*0.2;





	Color.rgb =vec3(diffuse)*col*shadow*vColor.xyz +spec	;
	Color.a	= alpha;


	
}