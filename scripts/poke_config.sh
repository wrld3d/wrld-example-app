#!/bin/sh

allArguments=$@

usage() { 
	echo "Usage: $0 -r <root_path> -i <input_config_file_path> -o <output_config_file_path> [-j <json_to_merge>]"; 1>&2; 
	echo "  -r -> path to root folder containing ApplicationConfigs (required)"; 1>&2; 
	echo "  -i -> relative path to input config file (required)"; 1>&2; 
	echo "  -o -> relative path to output config file (required)"; 1>&2; 	
	echo "  -j -> relative path to json file to merge with input config file to produce output config file"; 1>&2; 
	exit 1; 
}

json_to_poke="{}"

while getopts "r:i:o:j:" option; do
    case "${option}" in
        r)
            root_path=${OPTARG}
            ;;	
        i)
            input_config_file_path=${OPTARG}
            ;;
        o)
            output_config_file_path=${OPTARG}
            ;;			
        j)
            json_to_poke=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))


if [ -z "${root_path}" ]; then
    usage
	exit 1
fi
if [ -z "${input_config_file_path}" ]; then
    usage
	exit 1
fi
if [ -z "${output_config_file_path}" ]; then
    usage
	exit 1
fi

echo "json_to_poke is ${json_to_poke}"

script_dir=$(dirname $0)

apiKeyFile=${script_dir}/../src/ApiKey.h
apiKeyFileTemp=${apiKeyFile}_temp
git checkout $apiKeyFile

sed -e "s#\"ApplicationConfigs\/standard_config.json\"#\"${output_config_file_path}\"#g" $apiKeyFile > $apiKeyFileTemp

if [ $? -ne 0 ] ; then
echo "Failed to poke config file value into ApiKey file"  >&2
exit 1
fi

mv $apiKeyFileTemp $apiKeyFile

src_path="${root_path}/${input_config_file_path}"
dest_path="${root_path}/${output_config_file_path}"

git checkout $src_path

src_path_temp="src_config.bak"
cp -f $src_path $src_path_temp
rm -f $dest_path


python ${script_dir}/merge_json.py -i "${src_path_temp}" -o "${dest_path}" -j "${json_to_poke}"

resultcode=$?

rm -f $src_path_temp

if [ $resultcode -ne 0 ] ; then
  echo "failed to poke values into config json"
fi

exit $resultcode
