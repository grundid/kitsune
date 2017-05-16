#include "tinytensor_lstm_layer.h"
#include "tinytensor_conv_layer.h"
#include "tinytensor_fullyconnected_layer.h"
#include "tinytensor_math.h"
#include "tinytensor_net.h"
const static uint32_t LSTM_01_input_dims[4] = {1,1,1,40};
const static uint32_t LSTM_01_output_dims[4] = {1,1,1,8};
const static Weight_t __attribute__((section(".weights"))) LSTM_01_weights_input_gate_x[384] = {-316,-501,-30,-597,-19,457,1029,80,73,-281,-362,502,-8,297,-574,105,646,-27,205,196,-210,722,-318,75,439,-1,439,-371,-570,-157,-911,0,162,-830,149,223,-459,-548,470,-358,-1084,-316,-280,35,-289,1016,404,1342,-9,159,1,187,1210,694,117,1421,711,664,-275,-448,-40,-646,-1115,-970,-1170,-789,-842,-365,379,309,-474,-109,-676,-545,-585,-819,15,-763,-757,-401,554,-644,-497,-297,-401,-151,-166,-47,961,1402,-16,-678,759,-1410,-1158,1103,-491,470,780,493,1013,295,1177,139,270,515,324,-624,-373,296,-229,-365,656,214,550,7,-222,503,-489,298,200,88,-691,508,144,-78,-271,99,-746,198,406,18,-734,-599,290,268,841,172,1253,-204,-841,-980,-1247,542,-545,-232,-10,-430,755,-347,-343,-396,230,237,510,-326,-740,311,201,-669,-380,-303,195,430,-102,657,-317,-257,-326,237,169,263,462,-143,-159,213,-480,-97,766,-231,602,223,883,316,-701,-563,-655,-499,-701,-144,-1680,-703,-398,302,409,-138,849,-608,785,1120,-297,106,-620,-571,154,444,109,-56,252,205,-1010,-243,-492,-547,-131,567,-366,-143,-880,-632,187,496,-330,330,-615,-581,-920,216,-365,92,-40,5,169,764,-818,817,1204,3020,-348,-553,-205,-755,-47,745,560,-833,266,783,-22,970,147,59,611,854,172,1169,1035,1010,-163,-128,-253,755,-527,-525,54,200,-9,417,-363,578,-529,-827,-57,-321,-20,-579,507,694,294,-699,288,2240,771,-3046,37,72,-540,-454,-482,-56,311,-540,-276,333,-482,522,-222,458,710,663,691,149,-385,-16,367,172,-407,501,462,123,-530,687,-68,-148,-577,-266,190,-510,-390,834,441,79,-578,289,678,399,691,97,496,-1317,703,-91,1501,-57,-212,-436,-4,218,-278,889,581,53,317,0,-720,404,-358,108,-164,934,297,536,596,-299,249,-92,779,225,-359,357,-682,-221,375,588,186,594,-58,66,222,452,191,-393,-371,251,-83,286,-533,-45,1154,132,33,1331,54,-444};
const static uint32_t LSTM_01_weights_input_gate_dims[4] = {1,1,8,48};
const static ConstTensor_t LSTM_01_weights_input_gate = {&LSTM_01_weights_input_gate_x[0],&LSTM_01_weights_input_gate_dims[0],-1};

const static Weight_t __attribute__((section(".weights"))) LSTM_01_biases_input_gate_x[8] = {-1867,789,1783,621,-3184,541,2274,2589};
const static uint32_t LSTM_01_biases_input_gate_dims[4] = {1,1,1,8};
const static ConstTensor_t LSTM_01_biases_input_gate = {&LSTM_01_biases_input_gate_x[0],&LSTM_01_biases_input_gate_dims[0],1};

const static Weight_t __attribute__((section(".weights"))) LSTM_01_weights_cell_x[384] = {-330,635,484,1376,514,920,52,228,541,255,364,-633,264,262,-166,198,-462,-109,31,605,212,426,510,390,9,149,-480,-451,-32,64,-635,73,104,-268,-89,426,-770,580,-679,-97,-526,-71,-1292,-1427,-982,274,1118,-328,-229,-125,50,961,373,176,463,596,624,416,-1,411,-939,260,-58,-23,648,-526,-625,-316,-183,143,-278,-173,547,478,-186,181,866,905,773,-146,651,437,96,496,-398,188,-633,1396,-1560,-1259,-120,1339,-788,-2074,390,-1535,448,439,-194,-396,-1435,395,-863,-721,-91,585,68,371,-579,615,-98,-537,416,-239,-683,-127,459,-517,123,35,-54,-309,-587,-292,-798,-153,-536,-157,-612,596,-434,198,-772,171,-771,-507,-841,911,-83,-1518,2460,126,-1287,225,-186,-269,-84,386,-299,-835,-224,181,-765,-182,-551,-882,-684,73,-832,-902,-347,-831,516,-618,-146,-628,69,-250,470,71,369,-876,-674,-827,352,-341,366,408,42,518,1105,-15,275,748,1597,-926,-1245,-118,-916,482,-1315,-225,686,495,425,477,-214,-154,-21,212,-1146,-230,-276,-573,-482,52,123,-85,-107,471,857,-666,949,195,-394,246,-373,-32,-698,-517,-942,-130,316,559,-299,18,343,-497,185,655,1,474,743,135,-708,1319,339,-2483,-880,-50,-757,246,50,1693,-40,663,880,588,582,4,804,1222,-198,301,-110,327,590,390,825,304,524,-283,-383,567,336,-92,302,933,654,-534,7,-2,-495,-602,-1117,-867,-1113,86,-758,407,-150,1751,998,512,16,1287,689,-2297,184,-383,271,-461,-376,248,-555,-514,-779,-138,-688,-731,138,362,-509,-638,449,-321,-621,212,-505,-317,196,285,109,-313,-716,-575,-344,-486,-437,-660,299,59,282,513,-145,-157,-224,265,-661,-88,-723,1029,-316,1657,62,-724,316,23,400,1947,378,1114,571,548,705,100,901,-24,-410,651,670,755,714,101,50,155,715,-96,104,390,718,-240,-8,811,-334,-442,-545,-823,-228,-706,-963,-1175,-785,-777,-519,114,-1145,96,1089,-125,-930,290,-1103,130};
const static uint32_t LSTM_01_weights_cell_dims[4] = {1,1,8,48};
const static ConstTensor_t LSTM_01_weights_cell = {&LSTM_01_weights_cell_x[0],&LSTM_01_weights_cell_dims[0],-1};

const static Weight_t __attribute__((section(".weights"))) LSTM_01_biases_cell_x[8] = {-226,-1063,483,864,1180,-783,-2118,2109};
const static uint32_t LSTM_01_biases_cell_dims[4] = {1,1,1,8};
const static ConstTensor_t LSTM_01_biases_cell = {&LSTM_01_biases_cell_x[0],&LSTM_01_biases_cell_dims[0],0};

const static Weight_t __attribute__((section(".weights"))) LSTM_01_weights_forget_gate_x[384] = {112,-146,985,-482,-1021,-16,261,-299,498,-690,-767,257,167,-166,418,-332,313,-85,-411,-518,72,357,263,-486,-389,307,660,640,-85,-499,-400,-85,793,-411,757,982,-147,1007,80,62,9,172,-102,-629,980,557,-620,-314,476,-262,-766,-789,4,982,1069,1014,959,694,-347,-595,-715,-548,-444,483,188,30,374,-243,106,515,-783,-585,541,441,-221,180,257,609,-67,-605,212,-784,45,-728,671,-375,-215,-604,1456,1272,541,-24,618,520,-547,-2037,-1095,45,-518,49,156,-669,155,466,158,-1024,-360,-884,-1013,-89,-911,-472,-220,-24,-3,-186,90,79,-732,-165,-825,258,-658,194,-741,-138,-172,78,431,-92,211,-90,-567,326,-1008,-178,1342,40,-709,-842,270,1675,735,904,1287,373,-552,-86,397,-181,-167,620,935,-409,-127,481,-653,-565,244,650,-24,21,658,376,240,106,-205,479,-425,-526,-697,-285,-30,-57,556,-655,312,-744,347,-8,268,-186,483,171,13,-77,-1540,-860,-157,-6,9,-869,-144,78,-46,35,-439,-476,109,-36,-669,-300,-417,77,513,-68,-740,277,-452,293,-366,-457,-618,-77,-240,541,495,-603,74,496,-5,-520,-18,118,961,308,601,-266,596,517,-215,173,314,-108,-1343,-1377,-543,-151,-1332,1137,-435,261,165,-609,-838,-2362,-1143,82,-492,633,69,642,-446,310,-378,990,489,-332,183,68,-154,-67,-743,-702,-268,-210,-852,169,-344,-54,-179,-341,-473,-201,876,-100,1099,371,-181,-774,-143,-642,-45,-12,1043,2570,853,-297,-365,-597,-420,786,-43,509,-260,378,-79,-140,207,837,829,313,-109,349,-132,623,40,793,536,246,819,173,53,-302,-397,-4,-562,-505,-212,183,-623,407,612,16,-170,158,-521,177,217,951,-1391,0,1007,-1046,-34,421,-578,-1132,397,479,-62,596,1,-33,-86,1116,489,247,-204,-675,706,27,-12,396,618,415,-195,-300,-123,297,-649,-132,-452,221,-587,164,-525,343,-198,-226,-922,-702,216,348,800,-856,834,-1067,-322,1054,621,173,-568,-202};
const static uint32_t LSTM_01_weights_forget_gate_dims[4] = {1,1,8,48};
const static ConstTensor_t LSTM_01_weights_forget_gate = {&LSTM_01_weights_forget_gate_x[0],&LSTM_01_weights_forget_gate_dims[0],-1};

const static Weight_t __attribute__((section(".weights"))) LSTM_01_biases_forget_gate_x[8] = {2186,1732,2193,1938,1778,1485,2940,2368};
const static uint32_t LSTM_01_biases_forget_gate_dims[4] = {1,1,1,8};
const static ConstTensor_t LSTM_01_biases_forget_gate = {&LSTM_01_biases_forget_gate_x[0],&LSTM_01_biases_forget_gate_dims[0],-1};

const static Weight_t __attribute__((section(".weights"))) LSTM_01_weights_output_gate_x[384] = {-146,-831,953,653,858,1028,-68,-484,-237,130,-340,-801,-859,-121,536,-744,120,-217,129,390,-211,315,825,689,-584,-120,720,186,-90,-136,444,-353,-53,107,657,365,422,559,-565,-883,1871,1028,-28,191,-604,-967,-1147,-126,-196,-13,-377,577,212,920,624,-38,335,-173,210,501,812,724,300,-323,-207,-128,805,894,-32,-127,69,891,-93,44,911,365,752,742,28,454,1043,35,89,993,625,-212,-113,-253,568,398,-1004,65,631,416,-1106,1535,-183,333,530,241,-354,770,1157,649,838,-189,-176,-305,-324,650,327,795,891,81,299,521,377,-232,187,132,-293,696,-735,-506,724,-344,69,669,-503,-197,359,-244,186,-532,-325,647,873,110,327,399,1504,173,147,136,556,-78,30,-318,-38,537,780,1339,360,436,381,-331,328,346,380,587,34,-289,273,9,323,328,-524,-541,48,-805,-518,-458,552,-348,368,-370,47,224,662,-247,260,117,629,-604,1759,-801,-1106,1025,-741,-813,546,1043,234,-124,85,317,984,770,-192,428,425,926,436,522,906,-310,-261,-110,-325,-321,246,219,420,-442,485,-584,-238,-308,769,161,320,1050,-179,206,573,565,594,-609,-327,-212,857,523,326,1339,14,-1957,-139,450,1567,-119,497,209,-237,363,465,337,774,-92,244,-113,746,464,1068,617,1031,531,492,1111,-332,-162,268,56,844,378,-196,753,204,844,67,648,-73,5,564,104,119,-203,841,-90,421,210,-666,1604,1577,-674,101,352,461,669,13,-223,253,717,1538,1031,431,767,-93,-579,-466,-1045,306,423,-369,-89,411,720,-230,561,485,882,395,-129,-185,303,704,-289,228,868,802,549,-105,155,305,-416,-53,153,69,-236,320,964,-2036,1164,1123,-553,-72,-1146,270,-308,-778,-273,78,403,-440,-47,-289,-72,140,430,-70,349,-150,-365,-172,43,-246,-489,824,33,-288,-96,44,-61,-88,-339,88,283,-471,508,-325,787,728,680,739,417,191,314,218,-1027,113,-1178,1555,-1181,-114,-62};
const static uint32_t LSTM_01_weights_output_gate_dims[4] = {1,1,8,48};
const static ConstTensor_t LSTM_01_weights_output_gate = {&LSTM_01_weights_output_gate_x[0],&LSTM_01_weights_output_gate_dims[0],-1};

const static Weight_t __attribute__((section(".weights"))) LSTM_01_biases_output_gate_x[8] = {1128,1598,2443,1803,-617,-815,251,363};
const static uint32_t LSTM_01_biases_output_gate_dims[4] = {1,1,1,8};
const static ConstTensor_t LSTM_01_biases_output_gate = {&LSTM_01_biases_output_gate_x[0],&LSTM_01_biases_output_gate_dims[0],0};

const static LstmLayer_t lstm_01 = {&LSTM_01_weights_input_gate,&LSTM_01_biases_input_gate,&LSTM_01_weights_cell,&LSTM_01_biases_cell,&LSTM_01_weights_forget_gate,&LSTM_01_biases_forget_gate,&LSTM_01_weights_output_gate,&LSTM_01_biases_output_gate,LSTM_01_output_dims,LSTM_01_input_dims,TOFIX(0.000000),tinytensor_tanh};


const static Weight_t __attribute__((section(".weights"))) TimeDistributed_01_full_x[16] = {-2807,702,-3293,3019,3147,-2796,-1110,503,898,967,-3174,3532,1493,-470,1862,-82};
const static uint32_t TimeDistributed_01_full_dims[4] = {1,1,8,2};
const static ConstTensor_t TimeDistributed_01_full = {&TimeDistributed_01_full_x[0],&TimeDistributed_01_full_dims[0],-1};

const static Weight_t __attribute__((section(".weights"))) TimeDistributed_01_bias_x[2] = {3312,-3312};
const static uint32_t TimeDistributed_01_bias_dims[4] = {2,1,1,1};
const static ConstTensor_t TimeDistributed_01_bias = {&TimeDistributed_01_bias_x[0],&TimeDistributed_01_bias_dims[0],2};

const static uint32_t TimeDistributed_01_input_dims[4] = {1,1,1,8};
const static uint32_t TimeDistributed_01_output_dims[4] = {1,1,1,2};
const static FullyConnectedLayer_t timedistributed_01 = {&TimeDistributed_01_full,&TimeDistributed_01_bias,TimeDistributed_01_output_dims,TimeDistributed_01_input_dims,TOFIX(0.000000),tinytensor_linear,1};






static ConstLayer_t _layers[2];
static ConstSequentialNetwork_t net = {&_layers[0],2};
static ConstSequentialNetwork_t initialize_network(void) {

  _layers[0] = tinytensor_create_lstm_layer(&lstm_01);
  _layers[1] = tinytensor_create_fullyconnected_layer(&timedistributed_01);
  return net;

}