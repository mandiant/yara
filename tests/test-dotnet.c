#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <yara.h>

#include "util.h"

int main(int argc, char** argv)
{
  int result = 0;

  YR_DEBUG_INITIALIZE();
  YR_DEBUG_FPRINTF(1, stderr, "+ %s() { // in %s\n", __FUNCTION__, argv[0]);

  init_top_srcdir();

  yr_initialize();

  assert_true_rule_file(
      "import \"dotnet\" \
      rule test { \
        condition: \
          not dotnet.is_dotnet \
      }",
      "tests/data/tiny");

  assert_true_rule_file(
      "import \"dotnet\" \
      rule test { \
        condition: \
          dotnet.is_dotnet and \
          dotnet.assembly.name == \"hpjsoaputility.Sv.resources\" \
      }",
      "tests/data/"
      "0ca09bde7602769120fadc4f7a4147347a7a97271370583586c9e587fd396171");

  assert_true_rule_file(
      "import \"dotnet\" \
      rule test { \
        condition: \
          dotnet.is_dotnet and \
          dotnet.number_of_resources == 1 and \
          dotnet.resources[0].offset == 724 and \
          dotnet.resources[0].length == 180 and \
          dotnet.resources[0].name == \"hpjsoaputility.XmlStreamSoapExtension.pt.resources\" \
      }",
      "tests/data/"
      "0ca09bde7602769120fadc4f7a4147347a7a97271370583586c9e587fd396171");

  assert_true_rule_file(
      "import \"dotnet\" \
      rule test { \
        condition: \
          dotnet.is_dotnet and \
          dotnet.number_of_guids == 1 and \
          dotnet.guids[0] == \"3764d539-e21a-4366-bc7c-b56fa67efbb0\" \
      }",
      "tests/data/"
      "0ca09bde7602769120fadc4f7a4147347a7a97271370583586c9e587fd396171");

  assert_true_rule_file(
      "import \"dotnet\" \
      rule test { \
        condition: \
          dotnet.is_dotnet and \
          dotnet.number_of_streams == 5 and \
          dotnet.streams[0].name == \"#~\" and \
          dotnet.streams[1].name == \"#Strings\" and \
          dotnet.streams[2].name == \"#US\" and \
          dotnet.streams[3].name == \"#GUID\" and \
          dotnet.streams[4].name == \"#Blob\" \
      }",
      "tests/data/"
      "0ca09bde7602769120fadc4f7a4147347a7a97271370583586c9e587fd396171");

  assert_true_rule_file(
      "import \"dotnet\" \
      rule test { \
        condition: \
          dotnet.is_dotnet and \
          dotnet.module_name == \"hpjsoaputility.Sv.resources.dll\" and \
          dotnet.version == \"v2.0.50727\" \
      }",
      "tests/data/"
      "0ca09bde7602769120fadc4f7a4147347a7a97271370583586c9e587fd396171");

  assert_true_rule_file(
      "import \"dotnet\" \
      rule test { \
        condition: \
          dotnet.is_dotnet and \
          dotnet.entry_point == 0 and \
          dotnet.flags & ( \
            dotnet.COMIMAGE_FLAGS_ILONLY & \
            dotnet.COMIMAGE_FLAGS_STRONGNAMESIGNED) == \
            dotnet.COMIMAGE_FLAGS_ILONLY & \
            dotnet.COMIMAGE_FLAGS_STRONGNAMESIGNED \
      }",
      "tests/data/"
      "0ca09bde7602769120fadc4f7a4147347a7a97271370583586c9e587fd396171");

  assert_true_rule_file(
      "import \"dotnet\" \
      rule test { \
        condition: \
          dotnet.is_dotnet and \
          for any typeref in dotnet.typerefs : ( \
            typeref.namespace == \"System.Reflection\" and \
            typeref.name == \"AssemblyTitleAttribute\") \
      }",
      "tests/data/"
      "3b8b90159fa9b6048cc5410c5d53f116943564e4d05b04a843f9b3d0540d0c1c");

  assert_true_rule_file(
      "import \"dotnet\" \
      rule test { \
        condition: \
          dotnet.is_dotnet and \
          dotnet.number_of_memberrefs == 6 and \
          dotnet.memberrefs[1].name == \".ctor\" \
      }",
      "tests/data/"
      "0ca09bde7602769120fadc4f7a4147347a7a97271370583586c9e587fd396171");

  yr_finalize();

  YR_DEBUG_FPRINTF(
      1, stderr, "} = %d // %s() in %s\n", result, __FUNCTION__, argv[0]);

  return result;
}