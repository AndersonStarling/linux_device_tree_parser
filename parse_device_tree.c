#include <stdio.h>
#include <stdlib.h>
#include <libfdt.h>

#define APP_DEVICE_TREE_PATH "/home/ntai/Linux_Embedded/u-boot/qemu.dtb"
#define APP_PARSED_NODE "/memory"

const char * string_prop[] =
{
    "clock-output-names",
    "compatible",
    "stdout-path",
    "device_type",
    "method"
};

const char * hex_prop[] =
{
    "phandle",
    "clock-frequency",
    "#clock-cells",
    "#address-cells",
    "interrupt-parent",
    "interrupts",
    "#interrupt-cells",
    "reg",
    "bank-width",
    "migrate",
    "cpu_on",
    "cpu_off",
    "cpu_suspend"
};

const char * non_prop_value[] =
{
    "always-on",
    "msi-controller",
    "ranges",
    "dma-coherent"
};

static void parse_node_info(void *dtb, int node_offset)
{
    int prop_len;
    uint16_t index = 0;
    uint16_t index_prop_value = 0;
    const char * string;
    uint32_t * value;

    /* for each non_prop_value */
    for(index = 0; index < sizeof(non_prop_value)/sizeof(const char *); index ++)
    {
        fdt_getprop(dtb, node_offset, non_prop_value[index], &prop_len);
        if(prop_len >= 0)
        {
            printf("%s\n", non_prop_value[index]);
        }
    }

    /* for each string_prop */
    uint32_t string_len = 0;
    for(index = 0; index < sizeof(string_prop)/sizeof(const char *); index ++)
    {
        string = fdt_getprop(dtb, node_offset, string_prop[index], &prop_len);
        if(prop_len >= 0)
        {
            printf("%s = ", string_prop[index]);
            /* for each string in string_prop */
            for(string_len = strlen(string) + 1; string_len <= prop_len; string_len += (strlen(string) + 1))
            {
                printf("%s ", string);
                string += string_len;
            }
            printf("\n");
        }
    }

    /* for each hex_prop */
    for(index = 0; index < sizeof(hex_prop)/sizeof(const char *); index ++)
    {
        value = (uint32_t *)fdt_getprop(dtb, node_offset, hex_prop[index], &prop_len);
        if(prop_len >= 0)
        {
            printf("%s = ", hex_prop[index]);
            /* for each value in hex_prop */
            for(index_prop_value = 0; index_prop_value < prop_len/sizeof(uint32_t); index_prop_value ++)
            {
                printf("0x%x ", fdt32_to_cpu(*value));
                value ++;
            }
            printf("\n");
        }
    }
}

int main(void)
{
    FILE *file_ptr = fopen(APP_DEVICE_TREE_PATH, "rb");
    int ret = 0;
    int len = 0;
    int node_offset = 0;
    const char * ret_string;

    if(NULL == file_ptr)
    {
        printf("open file failed\n");
    }

    /* copy file to dynamic buffer */
    fseek(file_ptr, 0, SEEK_END);
    long size = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    void *dtb = malloc(size);
    fread(dtb, 1, size, file_ptr);
    fclose(file_ptr);

    /* Check device tree header */
    ret = fdt_check_header(dtb);
    if(ret != 0)
    {
        printf("fdt_check_header failed\n");
    }

    /* parse node information */
    node_offset = fdt_path_offset(dtb, APP_PARSED_NODE);
    printf("%s:\n", APP_PARSED_NODE);
    if(node_offset < 0)
    {
        printf("could not find node\n");
    }

    parse_node_info(dtb, node_offset);

    /* parse sub-node information */
    int sub_node = 0;
    const char *string;
    fdt_for_each_subnode(sub_node, dtb, node_offset)
    {
        if(sub_node >= 0)
        {
            string = fdt_get_name(dtb, sub_node, NULL);
            printf("%s:\n", string);
            parse_node_info(dtb, sub_node);
        }
    }

    /* free dynamic buffer */
    free(dtb);

    return 0;
}


























