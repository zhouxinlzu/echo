#ifndef __ECHO_ZIP_ARCHIVE_H__
#define __ECHO_ZIP_ARCHIVE_H__

#include <engine/core/io/DataStream.h>
#include "Archive.h"
#include "ResourcePack.h"

namespace Echo
{
	/**
	 * ��Դ���浵
	 */
	class ZipArchive : public Archive 
	{
		EE_AUTO_MUTEX
	public:
		ZipArchive(const String& strName, const String& strArchType);
		virtual ~ZipArchive();

		// �Ƿ��Сд����
		bool isCaseSensitive(void) const;

		// ����
		void load();

		// ж��
		void unload();

		// ���ļ�
		DataStream* open(const String& strFilename);

		// ���������ļ�
		StringArray list(bool bRecursive = true, bool bDirs = false);

		// �г��ļ���Ϣ
		FileInfoList* listFileInfo(bool bDirs = false);

		// �Ƿ��Ѵ���
		bool exists(const String& strFilename);

		// �Ƿ��첽
		virtual bool isAsync(const char* fileName) { return false; }

		// �����첽���ػص�
		virtual bool addAsyncCompleteCallback(const Echo::String& name, EchoOpenResourceCb callback) { return false; }

	protected:
		ResourcePack		m_resourcePack;		// ��Դ��
		bool				mLoaded;			// ����״̬���Ƿ��Ѽ��سɹ�
	};

	/**
	 * ��Դ��������
	 */
	class ResourcePackDataStream : public MemoryDataStream
	{
	public:
		ResourcePackDataStream(const String& strName, void* pvMem, size_t uSize, bool bFreeOnClose = false, bool bReadOnly = false)
			:	MemoryDataStream(strName, pvMem, uSize, bFreeOnClose, bReadOnly) {}
	};
}

#endif