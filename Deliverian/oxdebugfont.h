#ifndef IKD_OX_OXDEBUGFONT_H
#define IKD_OX_OXDEBUGFONT_H

namespace OX {
	class DebugFont {
		DebugFont() {}

	public:
		// �\���I�v�V����
		struct Option {
			enum Align {
				LEFT, RIGHT, CENTER
			};
			bool clip;
			int clipWidth;
			Align align;
			Option() : clip(), clipWidth(), align(LEFT) {}
		};

		~DebugFont();

		// ������
		static bool initialize(void *device, unsigned maxStrNum, unsigned maxWorkingBufferSize);

		// �f�o�b�O�������ǉ�
		static bool print(int x, int y, unsigned color, const char *format, ...);

		// �f�o�b�O��������I�v�V�����t���Œǉ�
		static bool print(int x, int y, unsigned color, Option &option, const char *format, ...);

		// �`��
		static bool draw(void *device);

		// �o�b�t�@���N���A
		static void clear();

		// �I��������
		static void terminate();
	};
}

#endif
