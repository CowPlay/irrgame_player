// Copyright (C) 2002-2010 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in Irrlicht.h

#ifndef __C_OPEN_GL_FEATURE_MAP_H_INCLUDED__
#define __C_OPEN_GL_FEATURE_MAP_H_INCLUDED__

#include "playerCompileConfig.h"

#include "IOpenGLExtensionHandler.h"

#include <OpenGL/gl.h>

namespace irrgame
{
	namespace video
	{

		class COpenGLExtensionHandler: public IOpenGLExtensionHandler
		{
			public:

				//! Default constructor
				COpenGLExtensionHandler();

				// deferred initialization
				void initExtensions(bool stencilBuffer);

				//! queries the features of the driver, returns true if feature is available
				bool queryFeature(EVideoDriverFeatures feature) const;

				//! queries the features of the driver, returns true if feature is available
				bool isOpenGLFeatureAvailable(EOpenGLFeatures feature) const
				{
					return FeatureAvailable[feature];
				}

				//! show all features with availablity
				void dump() const;

			public:

//				// public access to the (loaded) extensions.
//				// general functions
//				void extGlActiveTexture(GLenum texture);
//				void extGlClientActiveTexture(GLenum texture);
//				void extGlPointParameterf(GLint loc, GLfloat f);
//				void extGlPointParameterfv(GLint loc, const GLfloat *v);
//				void extGlStencilFuncSeparate(GLenum frontfunc, GLenum backfunc,
//						GLint ref, GLuint mask);
//				void extGlStencilOpSeparate(GLenum face, GLenum fail,
//						GLenum zfail, GLenum zpass);
//				void extGlCompressedTexImage2D(GLenum target, GLint level,
//						GLenum internalformat, GLsizei width, GLsizei height,
//						GLint border, GLsizei imageSize, const void* data);
//
//				// shader programming
//				void extGlGenPrograms(GLsizei n, GLuint *programs);
//				void extGlBindProgram(GLenum target, GLuint program);
//				void extGlProgramString(GLenum target, GLenum format,
//						GLsizei len, const GLvoid *string);
//				void extGlLoadProgram(GLenum target, GLuint id, GLsizei len,
//						const GLubyte *string);
//				void extGlDeletePrograms(GLsizei n, const GLuint *programs);
//				void extGlProgramLocalParameter4fv(GLenum, GLuint,
//						const GLfloat *);
//				GLhandleARB extGlCreateShaderObject(GLenum shaderType);
//				// note: Due to the type confusion between shader_objects and OpenGL 2.0
//				// we have to add the ARB extension for proper method definitions in case
//				// that handleARB and uint are the same type
//				void extGlShaderSourceARB(GLhandleARB shader, int numOfStrings,
//						const char **strings, int *lenOfStrings);
//				void extGlCompileShaderARB(GLhandleARB shader);
//				GLhandleARB extGlCreateProgramObject(void);
//				void extGlAttachObject(GLhandleARB program, GLhandleARB shader);
//				void extGlLinkProgramARB(GLhandleARB program);
//				void extGlUseProgramObject(GLhandleARB prog);
//				void extGlDeleteObject(GLhandleARB object);
//				void extGlGetAttachedObjects(GLhandleARB program,
//						GLsizei maxcount, GLsizei* count, GLhandleARB* shaders);
//				void extGlGetInfoLog(GLhandleARB object, GLsizei maxLength,
//						GLsizei *length, GLcharARB *infoLog);
//				void extGlGetObjectParameteriv(GLhandleARB object, GLenum type,
//						GLint *param);
//				GLint extGlGetUniformLocationARB(GLhandleARB program,
//						const char *name);
//				void extGlUniform4fv(GLint location, GLsizei count,
//						const GLfloat *v);
//				void extGlUniform1iv(GLint loc, GLsizei count, const GLint *v);
//				void extGlUniform1fv(GLint loc, GLsizei count,
//						const GLfloat *v);
//				void extGlUniform2fv(GLint loc, GLsizei count,
//						const GLfloat *v);
//				void extGlUniform3fv(GLint loc, GLsizei count,
//						const GLfloat *v);
//				void extGlUniformMatrix2fv(GLint loc, GLsizei count,
//						GLboolean transpose, const GLfloat *v);
//				void extGlUniformMatrix3fv(GLint loc, GLsizei count,
//						GLboolean transpose, const GLfloat *v);
//				void extGlUniformMatrix4fv(GLint loc, GLsizei count,
//						GLboolean transpose, const GLfloat *v);
//				void extGlGetActiveUniformARB(GLhandleARB program, GLuint index,
//						GLsizei maxlength, GLsizei *length, GLint *size,
//						GLenum *type, GLcharARB *name);
//
//				// framebuffer objects
//				void extGlBindFramebuffer(GLenum target, GLuint framebuffer);
//				void extGlDeleteFramebuffers(GLsizei n,
//						const GLuint *framebuffers);
//				void extGlGenFramebuffers(GLsizei n, GLuint *framebuffers);
//				GLenum extGlCheckFramebufferStatus(GLenum target);
//				void extGlFramebufferTexture2D(GLenum target, GLenum attachment,
//						GLenum textarget, GLuint texture, GLint level);
//				void extGlBindRenderbuffer(GLenum target, GLuint renderbuffer);
//				void extGlDeleteRenderbuffers(GLsizei n,
//						const GLuint *renderbuffers);
//				void extGlGenRenderbuffers(GLsizei n, GLuint *renderbuffers);
//				void extGlRenderbufferStorage(GLenum target,
//						GLenum internalformat, GLsizei width, GLsizei height);
//				void extGlFramebufferRenderbuffer(GLenum target,
//						GLenum attachment, GLenum renderbuffertarget,
//						GLuint renderbuffer);
//				void extGlActiveStencilFace(GLenum face);
//				void extGlDrawBuffers(GLsizei n, const GLenum *bufs);
//
//				// vertex buffer object
//				void extGlGenBuffers(GLsizei n, GLuint *buffers);
//				void extGlBindBuffer(GLenum target, GLuint buffer);
//				void extGlBufferData(GLenum target, GLsizeiptrARB size,
//						const GLvoid *data, GLenum usage);
//				void extGlDeleteBuffers(GLsizei n, const GLuint *buffers);
//				void extGlBufferSubData(GLenum target, GLintptrARB offset,
//						GLsizeiptrARB size, const GLvoid *data);
//				void extGlGetBufferSubData(GLenum target, GLintptrARB offset,
//						GLsizeiptrARB size, GLvoid *data);
//				void *extGlMapBuffer(GLenum target, GLenum access);
//				GLboolean extGlUnmapBuffer(GLenum target);
//				GLboolean extGlIsBuffer(GLuint buffer);
//				void extGlGetBufferParameteriv(GLenum target, GLenum pname,
//						GLint *params);
//				void extGlGetBufferPointerv(GLenum target, GLenum pname,
//						GLvoid **params);
//				void extGlProvokingVertex(GLenum mode);
//				void extGlColorMaskIndexed(GLuint buf, GLboolean r, GLboolean g,
//						GLboolean b, GLboolean a);
//				void extGlEnableIndexed(GLenum target, GLuint index);
//				void extGlDisableIndexed(GLenum target, GLuint index);
//				void extGlBlendFuncIndexed(GLuint buf, GLenum src, GLenum dst);
//				void extGlProgramParameteri(GLuint program, GLenum pname,
//						GLint value);

		};

//		inline void COpenGLExtensionHandler::extGlActiveTexture(GLenum texture)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (MultiTextureExtension && pGlActiveTextureARB)
//			pGlActiveTextureARB(texture);
//#else
//			if (MultiTextureExtension)
//#ifdef GL_ARB_multitexture
//				glActiveTextureARB(texture);
//#else
//			glActiveTexture(texture);
//#endif
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlClientActiveTexture(
//				GLenum texture)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (MultiTextureExtension && pGlClientActiveTextureARB)
//			pGlClientActiveTextureARB(texture);
//#else
//			if (MultiTextureExtension)
//				glClientActiveTextureARB(texture);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGenPrograms(GLsizei n,
//				GLuint *programs)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGenProgramsARB)
//			pGlGenProgramsARB(n, programs);
//			else if (pGlGenProgramsNV)
//			pGlGenProgramsNV(n, programs);
//#elif defined(GL_ARB_vertex_program) || defined(GL_ARB_fragment_program)
//			glGenProgramsARB(n, programs);
//#elif defined(GL_NV_vertex_program) || defined(GL_NV_fragment_program)
//			glGenProgramsNV(n,programs);
//#else
//			os::Printer::log("glGenPrograms not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlBindProgram(GLenum target,
//				GLuint program)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlBindProgramARB)
//			pGlBindProgramARB(target, program);
//			else if (pGlBindProgramNV)
//			pGlBindProgramNV(target, program);
//#elif defined(GL_ARB_vertex_program) || defined(GL_ARB_fragment_program)
//			glBindProgramARB(target, program);
//#elif defined(GL_NV_vertex_program) || defined(GL_NV_fragment_program)
//			glBindProgramNV(target, program);
//#else
//			os::Printer::log("glBindProgram not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlProgramString(GLenum target,
//				GLenum format, GLsizei len, const GLvoid *string)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlProgramStringARB)
//			pGlProgramStringARB(target, format, len, string);
//#elif defined(GL_ARB_vertex_program) || defined(GL_ARB_fragment_program)
//			glProgramStringARB(target, format, len, string);
//#else
//			os::Printer::log("glProgramString not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlLoadProgram(GLenum target,
//				GLuint id, GLsizei len, const GLubyte *string)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlLoadProgramNV)
//			pGlLoadProgramNV(target, id, len, string);
//#elif defined(GL_NV_vertex_program) || defined(GL_NV_fragment_program)
//			glLoadProgramNV(target,id,len,string);
//#else
//			//os::Printer::log("glLoadProgram not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlDeletePrograms(GLsizei n,
//				const GLuint *programs)
//		{
//
//#if defined(GL_ARB_vertex_program) || defined(GL_ARB_fragment_program)
//			glDeleteProgramsARB(n, programs);
//#else
//			IRR_ASSERT(false);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlProgramLocalParameter4fv(
//				GLenum n, GLuint i, const GLfloat * f)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlProgramLocalParameter4fvARB)
//			pGlProgramLocalParameter4fvARB(n,i,f);
//#elif defined(GL_ARB_vertex_program) || defined(GL_ARB_fragment_program)
//			glProgramLocalParameter4fvARB(n, i, f);
//#else
//			os::Printer::log("glProgramLocalParameter4fv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline GLhandleARB COpenGLExtensionHandler::extGlCreateShaderObject(
//				GLenum shaderType)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlCreateShaderObjectARB)
//			return pGlCreateShaderObjectARB(shaderType);
//#elif defined(GL_ARB_shader_objects)
//			return glCreateShaderObjectARB(shaderType);
//#else
//			os::Printer::log("glCreateShaderObject not supported", ELL_ERROR);
//#endif
//			return 0;
//		}
//
//		inline void COpenGLExtensionHandler::extGlShaderSourceARB(
//				GLhandleARB shader, int numOfStrings, const char **strings,
//				int *lenOfStrings)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlShaderSourceARB)
//			pGlShaderSourceARB(shader, numOfStrings, strings, lenOfStrings);
//#elif defined(GL_ARB_shader_objects)
//			glShaderSourceARB(shader, numOfStrings, strings,
//					(GLint *) lenOfStrings);
//#else
//			os::Printer::log("glShaderSource not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlCompileShaderARB(
//				GLhandleARB shader)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlCompileShaderARB)
//			pGlCompileShaderARB(shader);
//#elif defined(GL_ARB_shader_objects)
//			glCompileShaderARB(shader);
//#else
//			os::Printer::log("glCompileShader not supported", ELL_ERROR);
//#endif
//		}
//
//		inline GLhandleARB COpenGLExtensionHandler::extGlCreateProgramObject(
//				void)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlCreateProgramObjectARB)
//			return pGlCreateProgramObjectARB();
//#elif defined(GL_ARB_shader_objects)
//			return glCreateProgramObjectARB();
//#else
//			os::Printer::log("glCreateProgramObject not supported", ELL_ERROR);
//#endif
//			return 0;
//		}
//
//		inline void COpenGLExtensionHandler::extGlAttachObject(
//				GLhandleARB program, GLhandleARB shader)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlAttachObjectARB)
//			pGlAttachObjectARB(program, shader);
//#elif defined(GL_ARB_shader_objects)
//			glAttachObjectARB(program, shader);
//#else
//			os::Printer::log("glAttachObject not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlLinkProgramARB(
//				GLhandleARB program)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlLinkProgramARB)
//			pGlLinkProgramARB(program);
//#elif defined(GL_ARB_shader_objects)
//			glLinkProgramARB(program);
//#else
//			os::Printer::log("glLinkProgram not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlUseProgramObject(
//				GLhandleARB prog)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlUseProgramObjectARB)
//			pGlUseProgramObjectARB(prog);
//#elif defined(GL_ARB_shader_objects)
//			glUseProgramObjectARB(prog);
//#else
//			os::Printer::log("glUseProgramObject not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlDeleteObject(
//				GLhandleARB object)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlDeleteObjectARB)
//			pGlDeleteObjectARB(object);
//#elif defined(GL_ARB_shader_objects)
//			glDeleteObjectARB(object);
//#else
//			os::Printer::log("glDeleteObject not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGetAttachedObjects(
//				GLhandleARB program, GLsizei maxcount, GLsizei* count,
//				GLhandleARB* shaders)
//		{
//			*count = 0;
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGetAttachedObjectsARB)
//			pGlGetAttachedObjectsARB(program, maxcount, count, shaders);
//#elif defined(GL_ARB_shader_objects)
//			glGetAttachedObjectsARB(program, maxcount, count, shaders);
//#else
//			os::Printer::log("glGetAttachedObjects not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGetInfoLog(GLhandleARB object,
//				GLsizei maxLength, GLsizei *length, GLcharARB *infoLog)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGetInfoLogARB)
//			pGlGetInfoLogARB(object, maxLength, length, infoLog);
//#elif defined(GL_ARB_shader_objects)
//			glGetInfoLogARB(object, maxLength, length, infoLog);
//#else
//			os::Printer::log("glGetInfoLog not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGetObjectParameteriv(
//				GLhandleARB object, GLenum type, GLint *param)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGetObjectParameterivARB)
//			pGlGetObjectParameterivARB(object, type, param);
//#elif defined(GL_ARB_shader_objects)
//			glGetObjectParameterivARB(object, type, param);
//#else
//			os::Printer::log("glGetObjectParameteriv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline GLint COpenGLExtensionHandler::extGlGetUniformLocationARB(
//				GLhandleARB program, const char *name)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGetUniformLocationARB)
//			return pGlGetUniformLocationARB(program, name);
//#elif defined(GL_ARB_shader_objects)
//			return glGetUniformLocationARB(program, name);
//#else
//			os::Printer::log("glGetUniformLocation not supported", ELL_ERROR);
//#endif
//			return 0;
//		}
//
//		inline void COpenGLExtensionHandler::extGlUniform4fv(GLint location,
//				GLsizei count, const GLfloat *v)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlUniform4fvARB)
//			pGlUniform4fvARB(location, count, v);
//#elif defined(GL_ARB_shader_objects)
//			glUniform4fvARB(location, count, v);
//#else
//			os::Printer::log("glUniform4fv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlUniform1iv(GLint loc,
//				GLsizei count, const GLint *v)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlUniform1ivARB)
//			pGlUniform1ivARB(loc, count, v);
//#elif defined(GL_ARB_shader_objects)
//			glUniform1ivARB(loc, count, v);
//#else
//			os::Printer::log("glUniform1iv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlUniform1fv(GLint loc,
//				GLsizei count, const GLfloat *v)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlUniform1fvARB)
//			pGlUniform1fvARB(loc, count, v);
//#elif defined(GL_ARB_shader_objects)
//			glUniform1fvARB(loc, count, v);
//#else
//			os::Printer::log("glUniform1fv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlUniform2fv(GLint loc,
//				GLsizei count, const GLfloat *v)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlUniform2fvARB)
//			pGlUniform2fvARB(loc, count, v);
//#elif defined(GL_ARB_shader_objects)
//			glUniform2fvARB(loc, count, v);
//#else
//			os::Printer::log("glUniform2fv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlUniform3fv(GLint loc,
//				GLsizei count, const GLfloat *v)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlUniform3fvARB)
//			pGlUniform3fvARB(loc, count, v);
//#elif defined(GL_ARB_shader_objects)
//			glUniform3fvARB(loc, count, v);
//#else
//			os::Printer::log("glUniform3fv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlUniformMatrix2fv(GLint loc,
//				GLsizei count, GLboolean transpose, const GLfloat *v)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlUniformMatrix2fvARB)
//			pGlUniformMatrix2fvARB(loc, count, transpose, v);
//#elif defined(GL_ARB_shader_objects)
//			glUniformMatrix2fvARB(loc, count, transpose, v);
//#else
//			os::Printer::log("glUniformMatrix2fv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlUniformMatrix3fv(GLint loc,
//				GLsizei count, GLboolean transpose, const GLfloat *v)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlUniformMatrix3fvARB)
//			pGlUniformMatrix3fvARB(loc, count, transpose, v);
//#elif defined(GL_ARB_shader_objects)
//			glUniformMatrix3fvARB(loc, count, transpose, v);
//#else
//			os::Printer::log("glUniformMatrix3fv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlUniformMatrix4fv(GLint loc,
//				GLsizei count, GLboolean transpose, const GLfloat *v)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlUniformMatrix4fvARB)
//			pGlUniformMatrix4fvARB(loc, count, transpose, v);
//#elif defined(GL_ARB_shader_objects)
//			glUniformMatrix4fvARB(loc, count, transpose, v);
//#else
//			os::Printer::log("glUniformMatrix4fv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGetActiveUniformARB(
//				GLhandleARB program, GLuint index, GLsizei maxlength,
//				GLsizei *length, GLint *size, GLenum *type, GLcharARB *name)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGetActiveUniformARB)
//			pGlGetActiveUniformARB(program, index, maxlength, length, size, type, name);
//#elif defined(GL_ARB_shader_objects)
//			glGetActiveUniformARB(program, index, maxlength, length, size, type,
//					name);
//#else
//			os::Printer::log("glGetActiveUniform not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlPointParameterf(GLint loc,
//				GLfloat f)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlPointParameterfARB)
//			pGlPointParameterfARB(loc, f);
//#elif defined(GL_ARB_point_parameters)
//			glPointParameterfARB(loc, f);
//#else
//			os::Printer::log("glPointParameterf not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlPointParameterfv(GLint loc,
//				const GLfloat *v)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlPointParameterfvARB)
//			pGlPointParameterfvARB(loc, v);
//#elif defined(GL_ARB_point_parameters)
//			glPointParameterfvARB(loc, v);
//#else
//			os::Printer::log("glPointParameterfv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlStencilFuncSeparate(
//				GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlStencilFuncSeparate)
//			pGlStencilFuncSeparate(frontfunc, backfunc, ref, mask);
//			else if (pGlStencilFuncSeparateATI)
//			pGlStencilFuncSeparateATI(frontfunc, backfunc, ref, mask);
//#elif defined(GL_VERSION_2_0)
//			glStencilFuncSeparate(frontfunc, backfunc, ref, mask);
//#elif defined(GL_ATI_separate_stencil)
//			glStencilFuncSeparateATI(frontfunc, backfunc, ref, mask);
//#else
//			os::Printer::log("glStencilFuncSeparate not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlStencilOpSeparate(GLenum face,
//				GLenum fail, GLenum zfail, GLenum zpass)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlStencilOpSeparate)
//			pGlStencilOpSeparate(face, fail, zfail, zpass);
//			else if (pGlStencilOpSeparateATI)
//			pGlStencilOpSeparateATI(face, fail, zfail, zpass);
//#elif defined(GL_VERSION_2_0)
//			glStencilOpSeparate(face, fail, zfail, zpass);
//#elif defined(GL_ATI_separate_stencil)
//			glStencilOpSeparateATI(face, fail, zfail, zpass);
//#else
//			os::Printer::log("glStencilOpSeparate not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlCompressedTexImage2D(
//				GLenum target, GLint level, GLenum internalformat,
//				GLsizei width, GLsizei height, GLint border, GLsizei imageSize,
//				const void* data)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlCompressedTexImage2D)
//			pGlCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
//#elif defined(GL_ARB_texture_compression)
//			glCompressedTexImage2D(target, level, internalformat, width, height,
//					border, imageSize, data);
//#else
//			os::Printer::log("glCompressedTexImage2D not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlBindFramebuffer(GLenum target,
//				GLuint framebuffer)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlBindFramebufferEXT)
//			pGlBindFramebufferEXT(target, framebuffer);
//#elif defined(GL_EXT_framebuffer_object)
//			glBindFramebufferEXT(target, framebuffer);
//#else
//			os::Printer::log("glBindFramebuffer not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlDeleteFramebuffers(GLsizei n,
//				const GLuint *framebuffers)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlDeleteFramebuffersEXT)
//			pGlDeleteFramebuffersEXT(n, framebuffers);
//#elif defined(GL_EXT_framebuffer_object)
//			glDeleteFramebuffersEXT(n, framebuffers);
//#else
//			os::Printer::log("glDeleteFramebuffers not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGenFramebuffers(GLsizei n,
//				GLuint *framebuffers)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGenFramebuffersEXT)
//			pGlGenFramebuffersEXT(n, framebuffers);
//#elif defined(GL_EXT_framebuffer_object)
//			glGenFramebuffersEXT(n, framebuffers);
//#else
//			os::Printer::log("glGenFramebuffers not supported", ELL_ERROR);
//#endif
//		}
//
//		inline GLenum COpenGLExtensionHandler::extGlCheckFramebufferStatus(
//				GLenum target)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlCheckFramebufferStatusEXT)
//			return pGlCheckFramebufferStatusEXT(target);
//			else
//			return 0;
//#elif defined(GL_EXT_framebuffer_object)
//			return glCheckFramebufferStatusEXT(target);
//#else
//			os::Printer::log("glCheckFramebufferStatus not supported", ELL_ERROR);
//			return 0;
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlFramebufferTexture2D(
//				GLenum target, GLenum attachment, GLenum textarget,
//				GLuint texture, GLint level)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlFramebufferTexture2DEXT)
//			pGlFramebufferTexture2DEXT(target, attachment, textarget, texture, level);
//#elif defined(GL_EXT_framebuffer_object)
//			glFramebufferTexture2DEXT(target, attachment, textarget, texture,
//					level);
//#else
//			os::Printer::log("glFramebufferTexture2D not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlBindRenderbuffer(
//				GLenum target, GLuint renderbuffer)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlBindRenderbufferEXT)
//			pGlBindRenderbufferEXT(target, renderbuffer);
//#elif defined(GL_EXT_framebuffer_object)
//			glBindRenderbufferEXT(target, renderbuffer);
//#else
//			os::Printer::log("glBindRenderbuffer not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlDeleteRenderbuffers(GLsizei n,
//				const GLuint *renderbuffers)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlDeleteRenderbuffersEXT)
//			pGlDeleteRenderbuffersEXT(n, renderbuffers);
//#elif defined(GL_EXT_framebuffer_object)
//			glDeleteRenderbuffersEXT(n, renderbuffers);
//#else
//			os::Printer::log("glDeleteRenderbuffers not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGenRenderbuffers(GLsizei n,
//				GLuint *renderbuffers)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGenRenderbuffersEXT)
//			pGlGenRenderbuffersEXT(n, renderbuffers);
//#elif defined(GL_EXT_framebuffer_object)
//			glGenRenderbuffersEXT(n, renderbuffers);
//#else
//			os::Printer::log("glGenRenderbuffers not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlRenderbufferStorage(
//				GLenum target, GLenum internalformat, GLsizei width,
//				GLsizei height)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlRenderbufferStorageEXT)
//			pGlRenderbufferStorageEXT(target, internalformat, width, height);
//#elif defined(GL_EXT_framebuffer_object)
//			glRenderbufferStorageEXT(target, internalformat, width, height);
//#else
//			os::Printer::log("glRenderbufferStorage not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlFramebufferRenderbuffer(
//				GLenum target, GLenum attachment, GLenum renderbuffertarget,
//				GLuint renderbuffer)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlFramebufferRenderbufferEXT)
//			pGlFramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer);
//#elif defined(GL_EXT_framebuffer_object)
//			glFramebufferRenderbufferEXT(target, attachment, renderbuffertarget,
//					renderbuffer);
//#else
//			os::Printer::log("glFramebufferRenderbuffer not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlActiveStencilFace(GLenum face)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlActiveStencilFaceEXT)
//			pGlActiveStencilFaceEXT(face);
//#elif defined(GL_EXT_stencil_two_side)
//			glActiveStencilFaceEXT(face);
//#else
//			os::Printer::log("glActiveStencilFace not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlDrawBuffers(GLsizei n,
//				const GLenum *bufs)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlDrawBuffersARB)
//			pGlDrawBuffersARB(n, bufs);
//			else if (pGlDrawBuffersATI)
//			pGlDrawBuffersATI(n, bufs);
//#elif defined(GL_ARB_draw_buffers)
//			glDrawBuffersARB(n, bufs);
//#elif defined(GL_ATI_draw_buffers)
//			glDrawBuffersATI(n, bufs);
//#else
//			os::Printer::log("glDrawBuffers not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGenBuffers(GLsizei n,
//				GLuint *buffers)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGenBuffersARB)
//			pGlGenBuffersARB(n, buffers);
//#elif defined(GL_ARB_vertex_buffer_object)
//			glGenBuffers(n, buffers);
//#else
//			os::Printer::log("glGenBuffers not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlBindBuffer(GLenum target,
//				GLuint buffer)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlBindBufferARB)
//			pGlBindBufferARB(target, buffer);
//#elif defined(GL_ARB_vertex_buffer_object)
//			glBindBuffer(target, buffer);
//#else
//			os::Printer::log("glBindBuffer not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlBufferData(GLenum target,
//				GLsizeiptrARB size, const GLvoid *data, GLenum usage)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlBufferDataARB)
//			pGlBufferDataARB(target, size, data, usage);
//#elif defined(GL_ARB_vertex_buffer_object)
//			glBufferData(target, size, data, usage);
//#else
//			os::Printer::log("glBufferData not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlDeleteBuffers(GLsizei n,
//				const GLuint *buffers)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlDeleteBuffersARB)
//			pGlDeleteBuffersARB(n, buffers);
//#elif defined(GL_ARB_vertex_buffer_object)
//			glDeleteBuffers(n, buffers);
//#else
//			os::Printer::log("glDeleteBuffers not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlBufferSubData(GLenum target,
//				GLintptrARB offset, GLsizeiptrARB size, const GLvoid *data)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlBufferSubDataARB)
//			pGlBufferSubDataARB(target, offset, size, data);
//#elif defined(GL_ARB_vertex_buffer_object)
//			glBufferSubData(target, offset, size, data);
//#else
//			os::Printer::log("glBufferSubData not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGetBufferSubData(
//				GLenum target, GLintptrARB offset, GLsizeiptrARB size,
//				GLvoid *data)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGetBufferSubDataARB)
//			pGlGetBufferSubDataARB(target, offset, size, data);
//#elif defined(GL_ARB_vertex_buffer_object)
//			glGetBufferSubData(target, offset, size, data);
//#else
//			os::Printer::log("glGetBufferSubData not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void *COpenGLExtensionHandler::extGlMapBuffer(GLenum target,
//				GLenum access)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlMapBufferARB)
//			return pGlMapBufferARB(target, access);
//			return 0;
//#elif defined(GL_ARB_vertex_buffer_object)
//			return glMapBuffer(target, access);
//#else
//			os::Printer::log("glMapBuffer not supported", ELL_ERROR);
//			return 0;
//#endif
//		}
//
//		inline GLboolean COpenGLExtensionHandler::extGlUnmapBuffer(
//				GLenum target)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlUnmapBufferARB)
//			return pGlUnmapBufferARB(target);
//			return false;
//#elif defined(GL_ARB_vertex_buffer_object)
//			return glUnmapBuffer(target);
//#else
//			os::Printer::log("glUnmapBuffer not supported", ELL_ERROR);
//			return false;
//#endif
//		}
//
//		inline GLboolean COpenGLExtensionHandler::extGlIsBuffer(GLuint buffer)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlIsBufferARB)
//			return pGlIsBufferARB(buffer);
//			return false;
//#elif defined(GL_ARB_vertex_buffer_object)
//			return glIsBuffer(buffer);
//#else
//			os::Printer::log("glDeleteBuffers not supported", ELL_ERROR);
//			return false;
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGetBufferParameteriv(
//				GLenum target, GLenum pname, GLint *params)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGetBufferParameterivARB)
//			pGlGetBufferParameterivARB(target, pname, params);
//#elif defined(GL_ARB_vertex_buffer_object)
//			glGetBufferParameteriv(target, pname, params);
//#else
//			os::Printer::log("glGetBufferParameteriv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlGetBufferPointerv(
//				GLenum target, GLenum pname, GLvoid **params)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (pGlGetBufferPointervARB)
//			pGlGetBufferPointervARB(target, pname, params);
//#elif defined(GL_ARB_vertex_buffer_object)
//			glGetBufferPointerv(target, pname, params);
//#else
//			os::Printer::log("glGetBufferPointerv not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlProvokingVertex(GLenum mode)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (FeatureAvailable[IRR_ARB_provoking_vertex] && pGlProvokingVertexARB)
//			pGlProvokingVertexARB(mode);
//			else if (FeatureAvailable[IRR_EXT_provoking_vertex] && pGlProvokingVertexEXT)
//			pGlProvokingVertexEXT(mode);
//#elif defined(GL_ARB_provoking_vertex)
//			glProvokingVertex(mode);
//#elif defined(GL_EXT_provoking_vertex)
//			glProvokingVertexEXT(mode);
//#else
//			os::Printer::log("glProvokingVertex not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlColorMaskIndexed(GLuint buf,
//				GLboolean r, GLboolean g, GLboolean b, GLboolean a)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (FeatureAvailable[IRR_EXT_draw_buffers2] && pGlColorMaskIndexedEXT)
//			pGlColorMaskIndexedEXT(buf, r, g, b, a);
//#elif defined(GL_EXT_draw_buffers2)
//			glColorMaskIndexedEXT(buf, r, g, b, a);
//#else
//			os::Printer::log("glColorMaskIndexed not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlEnableIndexed(GLenum target,
//				GLuint index)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (FeatureAvailable[IRR_EXT_draw_buffers2] && pGlEnableIndexedEXT)
//			pGlEnableIndexedEXT(target, index);
//#elif defined(GL_EXT_draw_buffers2)
//			glEnableIndexedEXT(target, index);
//#else
//			os::Printer::log("glEnableIndexed not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlDisableIndexed(GLenum target,
//				GLuint index)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (FeatureAvailable[IRR_EXT_draw_buffers2] && pGlDisableIndexedEXT)
//			pGlDisableIndexedEXT(target, index);
//#elif defined(GL_EXT_draw_buffers2)
//			glDisableIndexedEXT(target, index);
//#else
//			os::Printer::log("glDisableIndexed not supported", ELL_ERROR);
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlBlendFuncIndexed(GLuint buf,
//				GLenum src, GLenum dst)
//		{
//#ifdef _IRR_OPENGL_USE_EXTPOINTER_
//			if (FeatureAvailable[IRR_ARB_draw_buffers_blend] && pGlBlendFunciARB)
//			pGlBlendFunciARB(buf, src, dst);
//			if (FeatureAvailable[IRR_AMD_draw_buffers_blend] && pGlBlendFuncIndexedAMD)
//			pGlBlendFuncIndexedAMD(buf, src, dst);
//#elif defined(GL_ARB_draw_buffers_blend)
//			glBlendFunciARB(buf, src, dst);
//#elif defined(GL_AMD_draw_buffers_blend)
//			glBlendFuncIndexedAMD(buf, src, dst);
//#else
//#endif
//		}
//
//		inline void COpenGLExtensionHandler::extGlProgramParameteri(
//				GLuint program, GLenum pname, GLint value)
//		{
//#if defined(_IRR_OPENGL_USE_EXTPOINTER_)
//			if (queryFeature(EVDF_GEOMETRY_SHADER))
//			{
//				if (pGlProgramParameteriARB)
//				pGlProgramParameteriARB(program, pname, value);
//				else if (pGlProgramParameteriEXT)
//				pGlProgramParameteriEXT(program, pname, value);
//			}
//#elif defined(GL_ARB_geometry_shader4)
//			glProgramParameteriARB(program, pname, value);
//#elif defined(GL_EXT_geometry_shader4)
//			glProgramParameteriEXT(program, pname, value);
//#elif defined(GL_NV_geometry_program4) || defined(GL_NV_geometry_shader4)
//			glProgramParameteriNV(program, pname, value);
//#else
//			os::Printer::log("glProgramParameteri not supported", ELL_ERROR);
//#endif
//		}

	}
}

#endif //__C_OPEN_GL_FEATURE_MAP_H_INCLUDED__
