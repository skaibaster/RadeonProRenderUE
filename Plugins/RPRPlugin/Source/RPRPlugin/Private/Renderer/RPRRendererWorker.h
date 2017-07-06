// RPR COPYRIGHT

#pragma once

class FRPRRendererWorker : public FRunnable
{
public:
	FRPRRendererWorker(rpr_context context);
	virtual ~FRPRRendererWorker();

	// Begin FRunnable interface.
	virtual bool	Init() override;
	virtual uint32	Run() override;
	virtual void	Stop() override;
	// End FRunnable interface

	void			EnsureCompletion();
	bool			Flush() const;
	bool			LockCopyFramebufferInto(void *outData);
private:
	void		ReleaseResources();
private:
	FRunnableThread			*m_Thread;
	FThreadSafeCounter		m_StopTaskCounter;
	FCriticalSection		m_RenderLock;

	uint32					m_CurrentIteration;
	uint32					m_PreviousRenderedIteration;

	rpr_framebuffer_format	m_RprFrameBufferFormat;
	rpr_framebuffer_desc	m_RprFrameBufferDesc;
	rpr_framebuffer			m_RprFrameBuffer;
	rpr_context				m_RprContext;

	TArray<float>			m_FramebufferData;
};
