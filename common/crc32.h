#ifndef MESSI_COMMON_CRC32_H
#define MESSI_COMMON_CRC32_H

#include "osl/include/inner_pre.h"

namespace osl {

    /** ������װ�˻���CRC32��У���������㷨��
    *  @remark ����㷨���ù̶���У���������������У���룬У��˫����Ҫ����ͬ�������
    *          ������ڳ���������ʱ���ʼ��һ�Σ�������ݲ��ܶ�̬�仯���߼��ء�
    *  @par    �����ֻ����2�����еľ�̬���������Ҳ��ܴ��������κ�ʱ��ʵ����
    *  @note   �����Ҫ���������м���/���ܷ�����Ҫ��������������Ķ�̬���÷�������
    *          �������ʱ���ʺϴ���Ӧ�á�
    *
    */
    class CRC32 {
    public:

        /** ���ù̶��������������У���롣
        *  @remark У���벻��<b>��֤���ظ�</b>�����Ƕ��ڵ�����У��Ŀ����˵�������ظ����ʱ�ʵ��
        *          ֤�����Ա�����Ӧ�ý��ܡ�
        *  @warning
        *  @param chData   Source data buffer, If length is length than dwLength, result is unkown.
        *  @param dwLength Size of chData.
        *  @return crc value.
        *  <code>
        *       unsigned int nCrc = CRC32::checksum(pBuf, nLen);
        *  <\code>
        */
        static unsigned int checksum( const void* chData, size_t dwLength );
        static unsigned int checksum(const std::string &src) { return checksum(src.c_str(), src.size()); }

    private:
        CRC32();
        CRC32( const CRC32& );

        // Initialize  table with 256 elements.
        static void Init_CRC32_Table (unsigned int *table);
        static unsigned int Reflect(unsigned int ref, char ch);
    };
}

#endif // MESSI_COMMON_CRC32_H
