#version 150 core
uniform float alpha;
uniform vec3 uLightPos;
uniform sampler2DShadow uShadowMap;

in vec4 vColor;
in vec4 vPosition;
in vec3 vNormal;
in vec4 vShadowCoord;

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
	vec3 Normal			= normalize( vNormal );
	vec3 lightDir		= normalize( uLightPos - vPosition.xyz );
	float NdotL			=  dot( vNormal, lightDir)*0.5 +0.5;
	
	vec3 Diffuse		= vec3( NdotL );
	vec3 Ambient		= vec3( 0.1 );
	

	 vec3 viewDir = normalize(uViewPos - vPosition.xyz);
    vec3 reflectDir = reflect(-lightDir, Normal	);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 2)*0.1;


	vec4 sc = vShadowCoord;
	vec4 ShadowCoord	= vShadowCoord / vShadowCoord.w;
	

	sc.z -= 0.005;
	float shadow = samplePCF4x4( sc );
	shadow =shadow*0.3+0.7;
	
	Color.rgb = ( Diffuse  * shadow  + Ambient  )* vColor.rgb +spec*shadow;
	Color.a	= alpha;

	
	
}