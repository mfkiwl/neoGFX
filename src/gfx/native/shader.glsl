#version 420
precision mediump float;

layout(binding = %UNIFORM_BLOCK_INDEX%) uniform %UNIFORM_BLOCK_NAME%
{
	%UNIFORMS%
};
%SINGULAR_UNIFORMS%
%VARIABLES%
