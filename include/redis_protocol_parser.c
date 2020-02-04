
#line 1 "redis_protocol_parser.rl"
/*
* Pedis is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* You may obtain a copy of the License at
*
*     http://www.gnu.org/licenses
*
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
* 
*  Copyright (c) 2016-2026, Peng Jian, pstack@163.com. All rights reserved.
*
*/

/** This protocol parser was inspired by the memcached app,
  which is the example in Seastar project.
**/

#include "core/ragel.hh"
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace seastar;


#line 208 "redis_protocol_parser.rl"


class redis_protocol_parser : public ragel_parser_base<redis_protocol_parser> {
    
#line 43 "redis_protocol_parser.c"
static const char _actions[] = {
	0, 1, 1, 1, 110, 2, 0, 1, 
	2, 3, 110, 2, 4, 110, 2, 5, 
	110, 2, 6, 110, 2, 8, 110, 2, 
	10, 110, 2, 11, 110, 2, 12, 110, 
	2, 13, 110, 2, 16, 110, 2, 17, 
	110, 2, 18, 110, 2, 19, 110, 2, 
	20, 110, 2, 21, 110, 2, 23, 110, 
	2, 24, 110, 2, 25, 110, 2, 26, 
	110, 2, 27, 110, 2, 28, 110, 2, 
	29, 110, 2, 31, 110, 2, 32, 110, 
	2, 33, 110, 2, 34, 110, 2, 35, 
	110, 2, 36, 110, 2, 37, 110, 2, 
	39, 110, 2, 40, 110, 2, 41, 110, 
	2, 43, 110, 2, 44, 110, 2, 45, 
	110, 2, 46, 110, 2, 47, 110, 2, 
	48, 110, 2, 49, 110, 2, 50, 110, 
	2, 51, 110, 2, 52, 110, 2, 53, 
	110, 2, 55, 110, 2, 57, 110, 2, 
	59, 110, 2, 60, 110, 2, 61, 110, 
	2, 62, 110, 2, 63, 110, 2, 64, 
	110, 2, 65, 110, 2, 66, 110, 2, 
	67, 110, 2, 68, 110, 2, 69, 110, 
	2, 70, 110, 2, 71, 110, 2, 73, 
	110, 2, 75, 110, 2, 76, 110, 2, 
	78, 110, 2, 79, 110, 2, 80, 110, 
	2, 81, 110, 2, 82, 110, 2, 83, 
	110, 2, 87, 110, 2, 88, 110, 2, 
	89, 110, 2, 90, 110, 2, 91, 110, 
	2, 92, 110, 2, 93, 110, 2, 94, 
	110, 2, 95, 110, 2, 96, 110, 2, 
	98, 110, 2, 99, 110, 2, 100, 110, 
	2, 101, 110, 2, 102, 110, 2, 103, 
	110, 2, 104, 110, 2, 105, 110, 2, 
	106, 110, 2, 107, 110, 2, 108, 110, 
	3, 2, 3, 110, 3, 10, 8, 110, 
	3, 14, 16, 110, 3, 15, 17, 110, 
	3, 19, 63, 110, 3, 23, 22, 110, 
	3, 26, 27, 110, 3, 28, 33, 110, 
	3, 31, 30, 110, 3, 35, 41, 110, 
	3, 42, 43, 110, 3, 46, 36, 110, 
	3, 47, 38, 110, 3, 51, 60, 110, 
	3, 53, 52, 110, 3, 55, 54, 110, 
	3, 57, 56, 110, 3, 59, 58, 110, 
	3, 62, 65, 110, 3, 64, 67, 110, 
	3, 69, 70, 110, 3, 78, 77, 110, 
	3, 80, 87, 110, 3, 82, 85, 110, 
	3, 89, 88, 110, 3, 98, 97, 110, 
	3, 99, 7, 110, 3, 100, 9, 110, 
	3, 108, 109, 110, 4, 5, 14, 16, 
	110, 4, 11, 15, 17, 110, 4, 12, 
	19, 63, 110, 4, 23, 22, 24, 110, 
	4, 31, 30, 32, 110, 4, 50, 57, 
	56, 110, 4, 71, 82, 85, 110, 4, 
	75, 76, 91, 110, 4, 78, 77, 79, 
	110, 4, 81, 84, 86, 110, 4, 89, 
	88, 72, 110, 4, 99, 7, 92, 110, 
	4, 105, 106, 107, 110, 5, 75, 76, 
	91, 74, 110, 5, 89, 73, 88, 72, 
	110, 5, 101, 104, 102, 103, 110, 7, 
	93, 94, 95, 96, 98, 97, 110, 8, 
	13, 64, 67, 66, 105, 106, 107, 110, 
	8, 75, 76, 91, 74, 78, 77, 79, 
	110, 9, 100, 9, 93, 94, 95, 96, 
	98, 97, 110, 11, 23, 22, 24, 25, 
	26, 27, 28, 29, 33, 34, 110, 12, 
	89, 73, 75, 76, 91, 74, 78, 77, 
	79, 88, 72, 110, 14, 35, 47, 38, 
	37, 39, 40, 41, 42, 43, 44, 45, 
	46, 36, 110, 19, 99, 7, 21, 48, 
	49, 50, 51, 53, 55, 54, 57, 56, 
	59, 58, 60, 52, 61, 92, 110, 25, 
	68, 69, 70, 71, 89, 73, 75, 76, 
	91, 74, 78, 77, 79, 80, 81, 82, 
	83, 84, 85, 86, 87, 88, 90, 72, 
	110
};

static const short _key_offsets[] = {
	0, 0, 1, 3, 6, 7, 8, 10, 
	13, 14, 46, 48, 50, 52, 54, 56, 
	57, 58, 59, 61, 64, 65, 66, 67, 
	69, 71, 79, 81, 83, 85, 87, 89, 
	91, 93, 95, 97, 99, 101, 103, 105, 
	107, 109, 111, 113, 115, 119, 121, 124, 
	126, 130, 132, 134, 138, 140, 142, 144, 
	146, 148, 150, 152, 156, 166, 168, 170, 
	172, 174, 176, 178, 180, 182, 184, 186, 
	188, 190, 192, 194, 196, 199, 201, 203, 
	205, 207, 209, 211, 213, 216, 218, 220, 
	238, 240, 242, 244, 246, 248, 250, 252, 
	254, 256, 259, 261, 263, 265, 267, 269, 
	271, 273, 276, 278, 280, 282, 284, 286, 
	288, 290, 292, 294, 298, 300, 302, 304, 
	306, 310, 312, 314, 316, 318, 320, 322, 
	324, 326, 328, 332, 334, 337, 339, 341, 
	343, 355, 357, 361, 363, 365, 367, 369, 
	371, 373, 375, 379, 381, 383, 385, 388, 
	392, 394, 396, 398, 400, 402, 404, 406, 
	408, 410, 414, 416, 418, 420, 422, 430, 
	434, 436, 438, 440, 442, 444, 446, 448, 
	450, 456, 458, 460, 462, 464, 466, 468, 
	470, 472, 474, 476, 478, 480, 482, 484, 
	486, 490, 492, 494, 496, 499, 519, 521, 
	523, 525, 527, 529, 531, 533, 535, 538, 
	540, 542, 544, 546, 550, 552, 554, 556, 
	559, 561, 563, 567, 569, 571, 573, 576, 
	578, 580, 582, 584, 586, 588, 590, 592, 
	594, 596, 600, 602, 604, 606, 608, 610, 
	612, 614, 616, 618, 622, 624, 626, 628, 
	630, 632, 634, 636, 638, 640, 642, 644, 
	646, 648, 650, 652, 654, 656, 659, 661, 
	663, 665, 667, 671, 673, 675, 677, 693, 
	695, 697, 701, 703, 705, 707, 709, 711, 
	713, 715, 717, 719, 721, 723, 725, 727, 
	729, 733, 735, 737, 739, 741, 743, 746, 
	748, 750, 752, 754, 756, 758, 760, 762, 
	764, 766, 768, 772, 774, 778, 780, 783, 
	785, 789, 791, 793, 795, 797, 799, 801, 
	805, 808, 810, 812, 814, 816, 818, 820, 
	826, 828, 830, 832, 834, 836, 838, 840, 
	842, 844, 846, 848, 850, 854, 856, 859, 
	861, 863, 865, 867, 869, 871, 873, 877, 
	879, 881, 883, 885, 887, 889, 891, 894, 
	896, 898, 900, 902, 902, 903
};

static const char _trans_keys[] = {
	42, 48, 57, 13, 48, 57, 10, 36, 
	48, 57, 13, 48, 57, 10, 65, 66, 
	67, 68, 69, 71, 72, 73, 74, 76, 
	77, 80, 82, 83, 84, 90, 97, 98, 
	99, 100, 101, 103, 104, 105, 106, 108, 
	109, 112, 114, 115, 116, 122, 80, 112, 
	80, 112, 69, 101, 78, 110, 68, 100, 
	13, 10, 36, 48, 57, 13, 48, 57, 
	10, 13, 10, 73, 105, 84, 116, 67, 
	70, 79, 80, 99, 102, 111, 112, 79, 
	111, 85, 117, 78, 110, 84, 116, 73, 
	105, 69, 101, 76, 108, 68, 100, 80, 
	112, 79, 111, 83, 115, 79, 111, 77, 
	109, 77, 109, 65, 97, 78, 110, 68, 
	100, 69, 101, 67, 76, 99, 108, 82, 
	114, 13, 66, 98, 89, 121, 67, 88, 
	99, 120, 72, 104, 79, 111, 73, 80, 
	105, 112, 83, 115, 84, 116, 83, 115, 
	73, 105, 82, 114, 69, 101, 69, 101, 
	79, 84, 111, 116, 65, 68, 72, 80, 
	82, 97, 100, 104, 112, 114, 68, 100, 
	68, 100, 73, 105, 83, 115, 84, 116, 
	65, 97, 83, 115, 72, 104, 79, 111, 
	83, 115, 65, 97, 68, 100, 73, 105, 
	85, 117, 83, 115, 13, 66, 98, 89, 
	121, 77, 109, 69, 101, 77, 109, 66, 
	98, 69, 101, 82, 114, 13, 66, 98, 
	73, 105, 84, 116, 68, 69, 71, 73, 
	75, 76, 77, 83, 86, 100, 101, 103, 
	105, 107, 108, 109, 115, 118, 69, 101, 
	76, 108, 88, 120, 73, 105, 83, 115, 
	84, 116, 83, 115, 69, 101, 84, 116, 
	13, 65, 97, 76, 108, 76, 108, 78, 
	110, 67, 99, 82, 114, 66, 98, 89, 
	121, 13, 70, 102, 76, 108, 79, 111, 
	65, 97, 84, 116, 69, 101, 89, 121, 
	83, 115, 69, 101, 78, 110, 71, 83, 
	103, 115, 69, 101, 84, 116, 69, 101, 
	84, 116, 69, 84, 101, 116, 84, 116, 
	82, 114, 76, 108, 69, 101, 78, 110, 
	65, 97, 76, 108, 83, 115, 78, 110, 
	67, 70, 99, 102, 82, 114, 13, 66, 
	98, 89, 121, 79, 111, 83, 115, 73, 
	76, 80, 82, 83, 84, 105, 108, 112, 
	114, 115, 116, 78, 110, 68, 83, 100, 
	115, 69, 101, 88, 120, 69, 101, 82, 
	114, 84, 116, 69, 101, 78, 110, 79, 
	85, 111, 117, 80, 112, 83, 115, 72, 
	104, 13, 88, 120, 65, 69, 97, 101, 
	78, 110, 71, 103, 69, 101, 77, 109, 
	69, 101, 84, 116, 82, 114, 73, 105, 
	77, 109, 71, 83, 103, 115, 69, 101, 
	84, 116, 69, 101, 84, 116, 69, 70, 
	73, 84, 101, 102, 105, 116, 82, 88, 
	114, 120, 83, 115, 73, 105, 83, 115, 
	84, 116, 80, 112, 73, 105, 82, 114, 
	69, 101, 65, 67, 77, 97, 99, 109, 
	68, 100, 68, 100, 79, 111, 85, 117, 
	78, 110, 84, 116, 69, 101, 82, 114, 
	71, 103, 69, 101, 78, 110, 71, 103, 
	84, 116, 76, 108, 80, 112, 79, 85, 
	111, 117, 80, 112, 83, 115, 72, 104, 
	13, 88, 120, 65, 67, 68, 69, 73, 
	77, 80, 82, 84, 85, 97, 99, 100, 
	101, 105, 109, 112, 114, 116, 117, 68, 
	100, 68, 100, 65, 97, 82, 114, 68, 
	100, 73, 105, 70, 102, 70, 102, 13, 
	83, 115, 84, 116, 79, 111, 82, 114, 
	69, 101, 76, 84, 108, 116, 69, 101, 
	67, 99, 84, 116, 13, 66, 98, 73, 
	105, 84, 116, 78, 83, 110, 115, 84, 
	116, 69, 101, 82, 114, 13, 83, 115, 
	84, 116, 79, 111, 82, 114, 69, 101, 
	77, 109, 69, 101, 77, 109, 66, 98, 
	69, 101, 82, 114, 69, 79, 101, 111, 
	77, 109, 66, 98, 69, 101, 82, 114, 
	83, 115, 86, 118, 69, 101, 79, 111, 
	80, 112, 65, 69, 97, 101, 78, 110, 
	68, 100, 77, 109, 69, 101, 77, 109, 
	66, 98, 69, 101, 82, 114, 77, 109, 
	82, 114, 76, 108, 69, 101, 78, 110, 
	78, 110, 73, 105, 79, 111, 78, 110, 
	13, 83, 115, 84, 116, 79, 111, 82, 
	114, 69, 101, 84, 89, 116, 121, 76, 
	108, 80, 112, 69, 101, 65, 67, 68, 
	73, 76, 82, 83, 85, 97, 99, 100, 
	105, 108, 114, 115, 117, 68, 100, 68, 
	100, 65, 79, 97, 111, 82, 114, 68, 
	100, 85, 117, 78, 110, 84, 116, 73, 
	105, 70, 102, 70, 102, 83, 115, 84, 
	116, 79, 111, 82, 114, 69, 101, 78, 
	110, 67, 84, 99, 116, 82, 114, 66, 
	98, 89, 121, 69, 101, 82, 114, 13, 
	83, 115, 84, 116, 79, 111, 82, 114, 
	69, 101, 69, 101, 88, 120, 67, 99, 
	79, 111, 85, 117, 78, 110, 84, 116, 
	65, 69, 97, 101, 78, 110, 71, 75, 
	103, 107, 69, 101, 13, 66, 98, 89, 
	121, 76, 83, 108, 115, 69, 101, 88, 
	120, 67, 99, 79, 111, 82, 114, 69, 
	101, 77, 86, 109, 118, 13, 82, 114, 
	65, 97, 78, 110, 71, 103, 69, 101, 
	66, 98, 89, 121, 76, 82, 83, 108, 
	114, 115, 69, 101, 88, 120, 65, 97, 
	78, 110, 75, 107, 67, 99, 79, 111, 
	82, 114, 69, 101, 82, 114, 65, 97, 
	78, 110, 71, 75, 103, 107, 69, 101, 
	13, 66, 98, 89, 121, 83, 115, 67, 
	99, 79, 111, 82, 114, 69, 101, 67, 
	99, 65, 79, 97, 111, 78, 110, 82, 
	114, 69, 101, 78, 110, 73, 105, 79, 
	111, 78, 110, 13, 83, 115, 84, 116, 
	79, 111, 82, 114, 69, 101, 36, 0
};

static const char _single_lengths[] = {
	0, 1, 0, 1, 1, 1, 0, 1, 
	1, 32, 2, 2, 2, 2, 2, 1, 
	1, 1, 0, 1, 1, 1, 1, 2, 
	2, 8, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 4, 2, 3, 2, 
	4, 2, 2, 4, 2, 2, 2, 2, 
	2, 2, 2, 4, 10, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 3, 2, 2, 2, 
	2, 2, 2, 2, 3, 2, 2, 18, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 4, 2, 2, 2, 2, 
	4, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 4, 2, 3, 2, 2, 2, 
	12, 2, 4, 2, 2, 2, 2, 2, 
	2, 2, 4, 2, 2, 2, 3, 4, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 4, 2, 2, 2, 2, 8, 4, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	6, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	4, 2, 2, 2, 3, 20, 2, 2, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 4, 2, 2, 2, 3, 
	2, 2, 4, 2, 2, 2, 3, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 4, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 4, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 3, 2, 2, 
	2, 2, 4, 2, 2, 2, 16, 2, 
	2, 4, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	4, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 4, 2, 4, 2, 3, 2, 
	4, 2, 2, 2, 2, 2, 2, 4, 
	3, 2, 2, 2, 2, 2, 2, 6, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 4, 2, 3, 2, 
	2, 2, 2, 2, 2, 2, 4, 2, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 0, 1, 0
};

static const char _range_lengths[] = {
	0, 0, 1, 1, 0, 0, 1, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const short _index_offsets[] = {
	0, 0, 2, 4, 7, 9, 11, 13, 
	16, 18, 51, 54, 57, 60, 63, 66, 
	68, 70, 72, 74, 77, 79, 81, 83, 
	86, 89, 98, 101, 104, 107, 110, 113, 
	116, 119, 122, 125, 128, 131, 134, 137, 
	140, 143, 146, 149, 152, 157, 160, 164, 
	167, 172, 175, 178, 183, 186, 189, 192, 
	195, 198, 201, 204, 209, 220, 223, 226, 
	229, 232, 235, 238, 241, 244, 247, 250, 
	253, 256, 259, 262, 265, 269, 272, 275, 
	278, 281, 284, 287, 290, 294, 297, 300, 
	319, 322, 325, 328, 331, 334, 337, 340, 
	343, 346, 350, 353, 356, 359, 362, 365, 
	368, 371, 375, 378, 381, 384, 387, 390, 
	393, 396, 399, 402, 407, 410, 413, 416, 
	419, 424, 427, 430, 433, 436, 439, 442, 
	445, 448, 451, 456, 459, 463, 466, 469, 
	472, 485, 488, 493, 496, 499, 502, 505, 
	508, 511, 514, 519, 522, 525, 528, 532, 
	537, 540, 543, 546, 549, 552, 555, 558, 
	561, 564, 569, 572, 575, 578, 581, 590, 
	595, 598, 601, 604, 607, 610, 613, 616, 
	619, 626, 629, 632, 635, 638, 641, 644, 
	647, 650, 653, 656, 659, 662, 665, 668, 
	671, 676, 679, 682, 685, 689, 710, 713, 
	716, 719, 722, 725, 728, 731, 734, 738, 
	741, 744, 747, 750, 755, 758, 761, 764, 
	768, 771, 774, 779, 782, 785, 788, 792, 
	795, 798, 801, 804, 807, 810, 813, 816, 
	819, 822, 827, 830, 833, 836, 839, 842, 
	845, 848, 851, 854, 859, 862, 865, 868, 
	871, 874, 877, 880, 883, 886, 889, 892, 
	895, 898, 901, 904, 907, 910, 914, 917, 
	920, 923, 926, 931, 934, 937, 940, 957, 
	960, 963, 968, 971, 974, 977, 980, 983, 
	986, 989, 992, 995, 998, 1001, 1004, 1007, 
	1010, 1015, 1018, 1021, 1024, 1027, 1030, 1034, 
	1037, 1040, 1043, 1046, 1049, 1052, 1055, 1058, 
	1061, 1064, 1067, 1072, 1075, 1080, 1083, 1087, 
	1090, 1095, 1098, 1101, 1104, 1107, 1110, 1113, 
	1118, 1122, 1125, 1128, 1131, 1134, 1137, 1140, 
	1147, 1150, 1153, 1156, 1159, 1162, 1165, 1168, 
	1171, 1174, 1177, 1180, 1183, 1188, 1191, 1195, 
	1198, 1201, 1204, 1207, 1210, 1213, 1216, 1221, 
	1224, 1227, 1230, 1233, 1236, 1239, 1242, 1246, 
	1249, 1252, 1255, 1258, 1259, 1261
};

static const short _indicies[] = {
	0, 1, 2, 1, 3, 4, 1, 5, 
	1, 6, 1, 7, 1, 8, 9, 1, 
	10, 1, 11, 12, 13, 14, 15, 16, 
	17, 18, 19, 20, 21, 22, 23, 24, 
	25, 26, 11, 12, 13, 14, 15, 16, 
	17, 18, 19, 20, 21, 22, 23, 24, 
	25, 26, 1, 27, 27, 1, 28, 28, 
	1, 29, 29, 1, 30, 30, 1, 31, 
	31, 1, 32, 1, 33, 1, 34, 1, 
	35, 1, 36, 37, 1, 38, 1, 39, 
	1, 40, 1, 41, 41, 1, 42, 42, 
	1, 43, 44, 45, 46, 43, 44, 45, 
	46, 1, 47, 47, 1, 48, 48, 1, 
	49, 49, 1, 50, 50, 1, 51, 51, 
	1, 52, 52, 1, 53, 53, 1, 54, 
	54, 1, 55, 55, 1, 56, 56, 1, 
	57, 57, 1, 58, 58, 1, 59, 59, 
	1, 60, 60, 1, 61, 61, 1, 62, 
	62, 1, 63, 63, 1, 64, 64, 1, 
	65, 66, 65, 66, 1, 67, 67, 1, 
	32, 68, 68, 1, 69, 69, 1, 70, 
	71, 70, 71, 1, 72, 72, 1, 73, 
	73, 1, 74, 75, 74, 75, 1, 76, 
	76, 1, 77, 77, 1, 78, 78, 1, 
	79, 79, 1, 80, 80, 1, 81, 81, 
	1, 82, 82, 1, 83, 84, 83, 84, 
	1, 85, 86, 87, 88, 89, 85, 86, 
	87, 88, 89, 1, 90, 90, 1, 91, 
	91, 1, 92, 92, 1, 93, 93, 1, 
	94, 94, 1, 95, 95, 1, 96, 96, 
	1, 97, 97, 1, 98, 98, 1, 99, 
	99, 1, 100, 100, 1, 101, 101, 1, 
	102, 102, 1, 103, 103, 1, 104, 104, 
	1, 32, 105, 105, 1, 106, 106, 1, 
	107, 107, 1, 108, 108, 1, 109, 109, 
	1, 110, 110, 1, 111, 111, 1, 112, 
	112, 1, 32, 113, 113, 1, 114, 114, 
	1, 115, 115, 1, 116, 117, 118, 119, 
	120, 121, 122, 123, 124, 116, 117, 118, 
	119, 120, 121, 122, 123, 124, 1, 125, 
	125, 1, 126, 126, 1, 127, 127, 1, 
	128, 128, 1, 129, 129, 1, 130, 130, 
	1, 131, 131, 1, 132, 132, 1, 133, 
	133, 1, 32, 134, 134, 1, 135, 135, 
	1, 136, 136, 1, 137, 137, 1, 138, 
	138, 1, 139, 139, 1, 140, 140, 1, 
	141, 141, 1, 32, 142, 142, 1, 143, 
	143, 1, 144, 144, 1, 145, 145, 1, 
	146, 146, 1, 147, 147, 1, 148, 148, 
	1, 149, 149, 1, 150, 150, 1, 151, 
	151, 1, 152, 153, 152, 153, 1, 154, 
	154, 1, 155, 155, 1, 156, 156, 1, 
	157, 157, 1, 158, 159, 158, 159, 1, 
	160, 160, 1, 161, 161, 1, 162, 162, 
	1, 163, 163, 1, 164, 164, 1, 165, 
	165, 1, 166, 166, 1, 167, 167, 1, 
	168, 168, 1, 169, 170, 169, 170, 1, 
	171, 171, 1, 32, 172, 172, 1, 173, 
	173, 1, 174, 174, 1, 175, 175, 1, 
	176, 177, 178, 179, 180, 181, 176, 177, 
	178, 179, 180, 181, 1, 182, 182, 1, 
	183, 184, 183, 184, 1, 185, 185, 1, 
	186, 186, 1, 187, 187, 1, 188, 188, 
	1, 189, 189, 1, 190, 190, 1, 191, 
	191, 1, 192, 193, 192, 193, 1, 194, 
	194, 1, 195, 195, 1, 196, 196, 1, 
	32, 197, 197, 1, 198, 199, 198, 199, 
	1, 200, 200, 1, 201, 201, 1, 202, 
	202, 1, 203, 203, 1, 204, 204, 1, 
	205, 205, 1, 206, 206, 1, 207, 207, 
	1, 208, 208, 1, 209, 210, 209, 210, 
	1, 211, 211, 1, 212, 212, 1, 213, 
	213, 1, 214, 214, 1, 215, 216, 217, 
	218, 215, 216, 217, 218, 1, 219, 220, 
	219, 220, 1, 221, 221, 1, 222, 222, 
	1, 223, 223, 1, 224, 224, 1, 225, 
	225, 1, 226, 226, 1, 227, 227, 1, 
	228, 228, 1, 229, 230, 231, 229, 230, 
	231, 1, 232, 232, 1, 233, 233, 1, 
	234, 234, 1, 235, 235, 1, 236, 236, 
	1, 237, 237, 1, 238, 238, 1, 239, 
	239, 1, 240, 240, 1, 241, 241, 1, 
	242, 242, 1, 243, 243, 1, 244, 244, 
	1, 245, 245, 1, 246, 246, 1, 247, 
	248, 247, 248, 1, 249, 249, 1, 250, 
	250, 1, 251, 251, 1, 32, 252, 252, 
	1, 253, 254, 255, 256, 257, 258, 259, 
	260, 261, 262, 253, 254, 255, 256, 257, 
	258, 259, 260, 261, 262, 1, 263, 263, 
	1, 264, 264, 1, 265, 265, 1, 266, 
	266, 1, 267, 267, 1, 268, 268, 1, 
	269, 269, 1, 270, 270, 1, 32, 271, 
	271, 1, 272, 272, 1, 273, 273, 1, 
	274, 274, 1, 275, 275, 1, 276, 277, 
	276, 277, 1, 278, 278, 1, 279, 279, 
	1, 280, 280, 1, 32, 281, 281, 1, 
	282, 282, 1, 283, 283, 1, 284, 285, 
	284, 285, 1, 286, 286, 1, 287, 287, 
	1, 288, 288, 1, 32, 289, 289, 1, 
	290, 290, 1, 291, 291, 1, 292, 292, 
	1, 293, 293, 1, 294, 294, 1, 295, 
	295, 1, 296, 296, 1, 297, 297, 1, 
	298, 298, 1, 299, 299, 1, 300, 301, 
	300, 301, 1, 302, 302, 1, 303, 303, 
	1, 304, 304, 1, 305, 305, 1, 306, 
	306, 1, 307, 307, 1, 308, 308, 1, 
	309, 309, 1, 310, 310, 1, 311, 312, 
	311, 312, 1, 313, 313, 1, 314, 314, 
	1, 315, 315, 1, 316, 316, 1, 317, 
	317, 1, 318, 318, 1, 319, 319, 1, 
	320, 320, 1, 321, 321, 1, 322, 322, 
	1, 323, 323, 1, 324, 324, 1, 325, 
	325, 1, 326, 326, 1, 327, 327, 1, 
	328, 328, 1, 329, 329, 1, 32, 330, 
	330, 1, 331, 331, 1, 332, 332, 1, 
	333, 333, 1, 334, 334, 1, 335, 336, 
	335, 336, 1, 337, 337, 1, 338, 338, 
	1, 339, 339, 1, 340, 341, 342, 343, 
	344, 345, 346, 347, 340, 341, 342, 343, 
	344, 345, 346, 347, 1, 348, 348, 1, 
	349, 349, 1, 350, 351, 350, 351, 1, 
	352, 352, 1, 353, 353, 1, 354, 354, 
	1, 355, 355, 1, 356, 356, 1, 357, 
	357, 1, 358, 358, 1, 359, 359, 1, 
	360, 360, 1, 361, 361, 1, 362, 362, 
	1, 363, 363, 1, 364, 364, 1, 365, 
	365, 1, 366, 367, 366, 367, 1, 368, 
	368, 1, 369, 369, 1, 370, 370, 1, 
	371, 371, 1, 372, 372, 1, 32, 373, 
	373, 1, 374, 374, 1, 375, 375, 1, 
	376, 376, 1, 377, 377, 1, 378, 378, 
	1, 379, 379, 1, 380, 380, 1, 381, 
	381, 1, 382, 382, 1, 383, 383, 1, 
	384, 384, 1, 385, 386, 385, 386, 1, 
	387, 387, 1, 388, 389, 388, 389, 1, 
	390, 390, 1, 32, 391, 391, 1, 392, 
	392, 1, 393, 394, 393, 394, 1, 395, 
	395, 1, 396, 396, 1, 397, 397, 1, 
	398, 398, 1, 399, 399, 1, 400, 400, 
	1, 401, 402, 401, 402, 1, 32, 403, 
	403, 1, 404, 404, 1, 405, 405, 1, 
	406, 406, 1, 407, 407, 1, 408, 408, 
	1, 409, 409, 1, 410, 411, 412, 410, 
	411, 412, 1, 413, 413, 1, 414, 414, 
	1, 415, 415, 1, 416, 416, 1, 417, 
	417, 1, 418, 418, 1, 419, 419, 1, 
	420, 420, 1, 421, 421, 1, 422, 422, 
	1, 423, 423, 1, 424, 424, 1, 425, 
	426, 425, 426, 1, 427, 427, 1, 32, 
	428, 428, 1, 429, 429, 1, 430, 430, 
	1, 431, 431, 1, 432, 432, 1, 433, 
	433, 1, 434, 434, 1, 435, 435, 1, 
	436, 437, 436, 437, 1, 438, 438, 1, 
	439, 439, 1, 440, 440, 1, 441, 441, 
	1, 442, 442, 1, 443, 443, 1, 444, 
	444, 1, 32, 445, 445, 1, 446, 446, 
	1, 447, 447, 1, 448, 448, 1, 449, 
	449, 1, 450, 34, 1, 451, 0
};

static const short _trans_targs[] = {
	2, 0, 3, 4, 3, 5, 6, 7, 
	8, 7, 9, 10, 23, 37, 43, 48, 
	58, 87, 129, 135, 136, 161, 166, 191, 
	197, 266, 270, 11, 12, 13, 14, 15, 
	16, 17, 18, 19, 20, 19, 21, 22, 
	364, 24, 25, 26, 30, 34, 35, 27, 
	28, 29, 15, 31, 32, 33, 15, 15, 
	36, 15, 38, 39, 40, 41, 42, 15, 
	44, 45, 15, 46, 47, 15, 49, 51, 
	50, 15, 52, 55, 53, 54, 15, 56, 
	57, 15, 59, 60, 84, 61, 63, 66, 
	69, 71, 62, 15, 64, 65, 15, 67, 
	68, 15, 70, 15, 72, 73, 74, 75, 
	76, 77, 78, 79, 80, 81, 82, 83, 
	15, 85, 86, 15, 88, 90, 95, 100, 
	110, 113, 115, 120, 126, 89, 15, 91, 
	92, 93, 94, 15, 96, 97, 98, 99, 
	15, 101, 102, 103, 104, 105, 106, 107, 
	108, 109, 15, 111, 112, 15, 114, 15, 
	116, 118, 117, 15, 119, 15, 121, 122, 
	15, 123, 124, 125, 15, 127, 128, 15, 
	130, 131, 134, 132, 133, 15, 15, 15, 
	137, 144, 146, 151, 156, 158, 138, 139, 
	141, 140, 15, 142, 143, 15, 145, 15, 
	147, 148, 15, 149, 150, 15, 152, 155, 
	153, 154, 15, 15, 157, 15, 159, 160, 
	15, 162, 164, 163, 15, 165, 15, 167, 
	176, 187, 189, 168, 172, 169, 170, 171, 
	15, 173, 174, 175, 15, 177, 179, 183, 
	178, 15, 180, 181, 182, 15, 184, 185, 
	186, 15, 188, 15, 190, 15, 192, 193, 
	194, 15, 195, 196, 15, 198, 200, 203, 
	211, 218, 233, 241, 243, 253, 257, 199, 
	15, 201, 202, 15, 204, 205, 206, 207, 
	208, 209, 210, 15, 212, 215, 213, 214, 
	15, 216, 217, 15, 219, 227, 220, 221, 
	222, 223, 224, 225, 226, 15, 228, 229, 
	230, 231, 232, 15, 234, 239, 235, 236, 
	237, 238, 15, 240, 15, 242, 15, 244, 
	252, 245, 246, 247, 248, 249, 250, 251, 
	15, 15, 254, 255, 256, 15, 258, 259, 
	260, 261, 262, 263, 264, 265, 15, 267, 
	268, 15, 269, 15, 271, 273, 279, 287, 
	299, 306, 349, 354, 272, 15, 274, 276, 
	275, 15, 277, 278, 15, 280, 281, 282, 
	283, 284, 285, 286, 15, 288, 289, 292, 
	290, 291, 15, 293, 294, 295, 296, 297, 
	298, 15, 300, 301, 302, 303, 304, 305, 
	15, 307, 319, 308, 309, 15, 310, 311, 
	312, 313, 315, 314, 15, 316, 317, 318, 
	15, 320, 337, 321, 322, 323, 324, 325, 
	326, 327, 328, 330, 333, 329, 15, 331, 
	332, 15, 334, 335, 336, 15, 338, 339, 
	340, 341, 15, 342, 343, 344, 345, 346, 
	347, 348, 15, 350, 351, 352, 15, 353, 
	15, 355, 356, 357, 358, 359, 360, 361, 
	362, 15, 365, 365
};

static const short _trans_actions[] = {
	3, 0, 272, 11, 8, 11, 3, 272, 
	269, 8, 269, 47, 465, 41, 393, 398, 
	497, 532, 388, 17, 507, 276, 479, 408, 
	547, 344, 567, 47, 47, 47, 47, 47, 
	3, 3, 3, 272, 269, 8, 384, 3, 
	3, 465, 465, 248, 254, 251, 257, 248, 
	248, 248, 248, 254, 254, 254, 254, 251, 
	257, 257, 41, 41, 41, 41, 41, 41, 
	393, 284, 26, 284, 38, 38, 29, 288, 
	29, 29, 44, 155, 44, 44, 44, 155, 
	155, 155, 497, 471, 380, 227, 230, 233, 
	236, 372, 227, 227, 230, 230, 230, 233, 
	233, 233, 236, 236, 372, 372, 372, 372, 
	372, 239, 239, 239, 239, 239, 239, 239, 
	239, 245, 245, 245, 92, 98, 320, 312, 
	107, 95, 316, 308, 110, 92, 92, 98, 
	98, 98, 98, 98, 320, 320, 116, 116, 
	116, 312, 312, 312, 312, 312, 104, 104, 
	104, 104, 104, 107, 107, 107, 95, 95, 
	113, 89, 113, 113, 89, 89, 86, 101, 
	86, 101, 101, 101, 101, 110, 110, 110, 
	388, 280, 14, 280, 35, 35, 14, 17, 
	296, 59, 403, 300, 71, 83, 296, 62, 
	65, 62, 62, 65, 65, 65, 59, 59, 
	56, 292, 56, 292, 292, 53, 68, 80, 
	68, 68, 68, 80, 71, 71, 83, 83, 
	83, 23, 20, 23, 23, 20, 20, 348, 
	448, 32, 164, 167, 158, 167, 167, 167, 
	167, 158, 158, 158, 158, 260, 263, 266, 
	260, 260, 263, 263, 263, 263, 266, 266, 
	266, 266, 32, 32, 164, 164, 408, 77, 
	304, 77, 304, 304, 74, 119, 122, 332, 
	443, 413, 324, 149, 328, 50, 340, 119, 
	119, 122, 122, 122, 332, 332, 332, 137, 
	137, 137, 137, 137, 224, 376, 224, 224, 
	224, 242, 242, 242, 336, 125, 336, 336, 
	336, 140, 140, 140, 140, 140, 125, 125, 
	125, 125, 125, 125, 128, 146, 128, 128, 
	128, 128, 128, 146, 146, 149, 149, 131, 
	134, 131, 131, 131, 131, 131, 131, 131, 
	131, 134, 50, 50, 50, 50, 340, 340, 
	340, 340, 143, 143, 143, 143, 143, 161, 
	152, 161, 152, 152, 170, 352, 206, 418, 
	218, 519, 360, 433, 170, 170, 173, 176, 
	173, 173, 176, 176, 176, 206, 206, 206, 
	206, 206, 206, 206, 206, 418, 179, 364, 
	179, 179, 179, 364, 364, 203, 203, 203, 
	203, 203, 218, 218, 218, 218, 218, 218, 
	218, 459, 488, 459, 438, 182, 438, 368, 
	368, 212, 215, 212, 212, 215, 215, 215, 
	215, 453, 428, 423, 423, 423, 423, 423, 
	423, 423, 221, 185, 188, 221, 221, 185, 
	185, 185, 188, 188, 188, 188, 428, 428, 
	428, 356, 194, 356, 191, 191, 191, 191, 
	191, 191, 191, 360, 209, 197, 209, 197, 
	197, 433, 433, 433, 433, 200, 200, 200, 
	200, 200, 5, 1
};

static const int start = 1;
static const int error = 0;

static const int en_blob = 363;
static const int en_main = 1;


#line 212 "redis_protocol_parser.rl"
public:
    enum class state {
        error,
        eof,
        ok,
    };
    enum class command {
        info,
        js,
        set,
        mset,
        get,
        mget,
        del,
        echo,
        ping,
        incr,
        decr,
        incrby,
        decrby,
        command,
        exists,
        append,
        strlen,
        lpush,
        lpushx,
        lpop,
        llen,
        lindex,
        linsert,
        lrange,
        lset,
        rpush,
        rpushx,
        rpop,
        lrem,
        ltrim,
        hset,
        hdel,
        hget,
        hlen,
        hexists,
        hstrlen,
        hincrby,
        hincrbyfloat,
        hkeys,
        hvals,
        hmget,
        hmset,
        hgetall,
        sadd,
        scard,
        sismember,
        smembers,
        srem,
        sdiff,
        sdiffstore,
        sinter,
        sinterstore,
        sunion,
        sunionstore,
        smove,
        srandmember,
        spop,
        type,
        expire,
        pexpire,
        ttl,
        pttl,
        persist,
        zadd,
        zcard,
        zcount,
        zincrby,
        zrange,
        zrangebyscore,
        zrank,
        zrem,
        zremrangebyrank,
        zremrangebyscore,
        zrevrange,
        zrevrangebyscore,
        zrevrank,
        zscore,
        zunionstore,
        zinterstore,
        zdiffstore,
        zunion,
        zinter,
        zdiff,
        zscan,
        zrangebylex,
        zlexcount,
        zremrangebylex,
        select,
        geoadd,
        geohash,
        geodist,
        geopos,
        georadius,
        georadiusbymember,
        setbit,
        getbit,
        bitcount,
        bitop,
        bitpos,
        bitfield,
        pfadd,
        pfcount,
        pfmerge,
    };

    state _state;
    command _command;
    uint32_t _u32;
    uint32_t _arg_size;
    uint32_t _args_count;
    uint32_t _size_left;
    std::vector<sstring>  _args_list;
public:
    void init() {
        init_base();
        _state = state::error;
        _args_list.clear();
        _args_count = 0;
        _size_left = 0;
        _arg_size = 0;
        
#line 851 "redis_protocol_parser.c"
	{
	 _fsm_cs = start;
	 _fsm_top = 0;
	}

#line 340 "redis_protocol_parser.rl"
    }

    char* parse(char* p, char* pe, char* eof) {
        sstring_builder::guard g(_builder, p, pe);
        auto str = [this, &g, &p] { g.mark_end(p); return get_str(); };
        
#line 864 "redis_protocol_parser.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if (  _fsm_cs == 0 )
		goto _out;
_resume:
	_keys = _trans_keys + _key_offsets[ _fsm_cs];
	_trans = _index_offsets[ _fsm_cs];

	_klen = _single_lengths[ _fsm_cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _range_lengths[ _fsm_cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _indicies[_trans];
	 _fsm_cs = _trans_targs[_trans];

	if ( _trans_actions[_trans] == 0 )
		goto _again;

	_acts = _actions + _trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 44 "redis_protocol_parser.rl"
	{
    g.mark_start(p);
    _size_left = _arg_size;
}
	break;
	case 1:
#line 53 "redis_protocol_parser.rl"
	{
    auto len = std::min((uint32_t)(pe - p), _size_left);
    _size_left -= len;
    p += len;
    if (_size_left == 0) {
      _args_list.push_back(str());
      p--;
      { _fsm_cs =  _fsm_stack[-- _fsm_top]; {
    postpop();
}goto _again;}
    }
    p--;
}
	break;
	case 2:
#line 79 "redis_protocol_parser.rl"
	{ _u32 = 0;}
	break;
	case 3:
#line 79 "redis_protocol_parser.rl"
	{ _u32 *= 10; _u32 += (*p) - '0';}
	break;
	case 4:
#line 80 "redis_protocol_parser.rl"
	{_args_count = _u32;}
	break;
	case 5:
#line 82 "redis_protocol_parser.rl"
	{_command = command::info;}
	break;
	case 6:
#line 83 "redis_protocol_parser.rl"
	{_command = command::js;}
	break;
	case 7:
#line 84 "redis_protocol_parser.rl"
	{_command = command::set;}
	break;
	case 8:
#line 85 "redis_protocol_parser.rl"
	{_command = command::mset;}
	break;
	case 9:
#line 86 "redis_protocol_parser.rl"
	{_command = command::get;}
	break;
	case 10:
#line 87 "redis_protocol_parser.rl"
	{_command = command::mget;}
	break;
	case 11:
#line 88 "redis_protocol_parser.rl"
	{_command = command::del;}
	break;
	case 12:
#line 89 "redis_protocol_parser.rl"
	{_command = command::echo;}
	break;
	case 13:
#line 90 "redis_protocol_parser.rl"
	{_command = command::ping;}
	break;
	case 14:
#line 91 "redis_protocol_parser.rl"
	{_command = command::incr;}
	break;
	case 15:
#line 92 "redis_protocol_parser.rl"
	{_command = command::decr;}
	break;
	case 16:
#line 93 "redis_protocol_parser.rl"
	{_command = command::incrby;}
	break;
	case 17:
#line 94 "redis_protocol_parser.rl"
	{_command = command::decrby;}
	break;
	case 18:
#line 95 "redis_protocol_parser.rl"
	{_command = command::command;}
	break;
	case 19:
#line 96 "redis_protocol_parser.rl"
	{_command = command::exists;}
	break;
	case 20:
#line 97 "redis_protocol_parser.rl"
	{_command = command::append;}
	break;
	case 21:
#line 98 "redis_protocol_parser.rl"
	{_command = command::strlen;}
	break;
	case 22:
#line 99 "redis_protocol_parser.rl"
	{_command = command::lpush;}
	break;
	case 23:
#line 100 "redis_protocol_parser.rl"
	{_command = command::lpushx;}
	break;
	case 24:
#line 101 "redis_protocol_parser.rl"
	{_command = command::lpop;}
	break;
	case 25:
#line 102 "redis_protocol_parser.rl"
	{_command = command::llen;}
	break;
	case 26:
#line 103 "redis_protocol_parser.rl"
	{_command = command::lindex;}
	break;
	case 27:
#line 104 "redis_protocol_parser.rl"
	{_command = command::linsert;}
	break;
	case 28:
#line 105 "redis_protocol_parser.rl"
	{_command = command::lrange;}
	break;
	case 29:
#line 106 "redis_protocol_parser.rl"
	{_command = command::lset;}
	break;
	case 30:
#line 107 "redis_protocol_parser.rl"
	{_command = command::rpush;}
	break;
	case 31:
#line 108 "redis_protocol_parser.rl"
	{_command = command::rpushx;}
	break;
	case 32:
#line 109 "redis_protocol_parser.rl"
	{_command = command::rpop;}
	break;
	case 33:
#line 110 "redis_protocol_parser.rl"
	{_command = command::lrem;}
	break;
	case 34:
#line 111 "redis_protocol_parser.rl"
	{_command = command::ltrim;}
	break;
	case 35:
#line 112 "redis_protocol_parser.rl"
	{_command = command::hset;}
	break;
	case 36:
#line 113 "redis_protocol_parser.rl"
	{_command = command::hmset;}
	break;
	case 37:
#line 114 "redis_protocol_parser.rl"
	{_command = command::hdel;}
	break;
	case 38:
#line 115 "redis_protocol_parser.rl"
	{_command = command::hget;}
	break;
	case 39:
#line 116 "redis_protocol_parser.rl"
	{_command = command::hlen;}
	break;
	case 40:
#line 117 "redis_protocol_parser.rl"
	{_command = command::hexists;}
	break;
	case 41:
#line 118 "redis_protocol_parser.rl"
	{_command = command::hstrlen;}
	break;
	case 42:
#line 119 "redis_protocol_parser.rl"
	{_command = command::hincrby;}
	break;
	case 43:
#line 120 "redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
	break;
	case 44:
#line 121 "redis_protocol_parser.rl"
	{_command = command::hkeys;}
	break;
	case 45:
#line 122 "redis_protocol_parser.rl"
	{_command = command::hvals;}
	break;
	case 46:
#line 123 "redis_protocol_parser.rl"
	{_command = command::hmget;}
	break;
	case 47:
#line 124 "redis_protocol_parser.rl"
	{_command = command::hgetall;}
	break;
	case 48:
#line 125 "redis_protocol_parser.rl"
	{_command = command::sadd;}
	break;
	case 49:
#line 126 "redis_protocol_parser.rl"
	{_command = command::scard;}
	break;
	case 50:
#line 127 "redis_protocol_parser.rl"
	{_command = command::sismember;}
	break;
	case 51:
#line 128 "redis_protocol_parser.rl"
	{_command = command::smembers;}
	break;
	case 52:
#line 129 "redis_protocol_parser.rl"
	{_command = command::srandmember;}
	break;
	case 53:
#line 130 "redis_protocol_parser.rl"
	{_command = command::srem;}
	break;
	case 54:
#line 131 "redis_protocol_parser.rl"
	{_command = command::sdiff;}
	break;
	case 55:
#line 132 "redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
	break;
	case 56:
#line 133 "redis_protocol_parser.rl"
	{_command = command::sinter;}
	break;
	case 57:
#line 134 "redis_protocol_parser.rl"
	{_command = command::sinterstore;}
	break;
	case 58:
#line 135 "redis_protocol_parser.rl"
	{_command = command::sunion;}
	break;
	case 59:
#line 136 "redis_protocol_parser.rl"
	{_command = command::sunionstore;}
	break;
	case 60:
#line 137 "redis_protocol_parser.rl"
	{_command = command::smove;}
	break;
	case 61:
#line 138 "redis_protocol_parser.rl"
	{_command = command::spop;}
	break;
	case 62:
#line 139 "redis_protocol_parser.rl"
	{_command = command::type; }
	break;
	case 63:
#line 140 "redis_protocol_parser.rl"
	{_command = command::expire; }
	break;
	case 64:
#line 141 "redis_protocol_parser.rl"
	{_command = command::pexpire; }
	break;
	case 65:
#line 142 "redis_protocol_parser.rl"
	{_command = command::ttl; }
	break;
	case 66:
#line 143 "redis_protocol_parser.rl"
	{_command = command::pttl; }
	break;
	case 67:
#line 144 "redis_protocol_parser.rl"
	{_command = command::persist; }
	break;
	case 68:
#line 145 "redis_protocol_parser.rl"
	{_command = command::zadd; }
	break;
	case 69:
#line 146 "redis_protocol_parser.rl"
	{_command = command::zcard; }
	break;
	case 70:
#line 147 "redis_protocol_parser.rl"
	{_command = command::zcount; }
	break;
	case 71:
#line 148 "redis_protocol_parser.rl"
	{_command = command::zincrby; }
	break;
	case 72:
#line 149 "redis_protocol_parser.rl"
	{_command = command::zrange;}
	break;
	case 73:
#line 150 "redis_protocol_parser.rl"
	{_command = command::zrank; }
	break;
	case 74:
#line 151 "redis_protocol_parser.rl"
	{_command = command::zrem; }
	break;
	case 75:
#line 152 "redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
	break;
	case 76:
#line 153 "redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
	break;
	case 77:
#line 154 "redis_protocol_parser.rl"
	{_command = command::zrevrange; }
	break;
	case 78:
#line 155 "redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
	break;
	case 79:
#line 156 "redis_protocol_parser.rl"
	{_command = command::zrevrank; }
	break;
	case 80:
#line 157 "redis_protocol_parser.rl"
	{_command = command::zscore; }
	break;
	case 81:
#line 158 "redis_protocol_parser.rl"
	{_command = command::zunionstore; }
	break;
	case 82:
#line 159 "redis_protocol_parser.rl"
	{_command = command::zinterstore; }
	break;
	case 83:
#line 160 "redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
	break;
	case 84:
#line 161 "redis_protocol_parser.rl"
	{_command = command::zunion; }
	break;
	case 85:
#line 162 "redis_protocol_parser.rl"
	{_command = command::zinter; }
	break;
	case 86:
#line 163 "redis_protocol_parser.rl"
	{_command = command::zdiff; }
	break;
	case 87:
#line 164 "redis_protocol_parser.rl"
	{_command = command::zscan; }
	break;
	case 88:
#line 165 "redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
	break;
	case 89:
#line 166 "redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
	break;
	case 90:
#line 167 "redis_protocol_parser.rl"
	{_command = command::zlexcount;}
	break;
	case 91:
#line 168 "redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
	break;
	case 92:
#line 169 "redis_protocol_parser.rl"
	{_command = command::select; }
	break;
	case 93:
#line 170 "redis_protocol_parser.rl"
	{_command = command::geoadd; }
	break;
	case 94:
#line 171 "redis_protocol_parser.rl"
	{_command = command::geodist; }
	break;
	case 95:
#line 172 "redis_protocol_parser.rl"
	{_command = command::geohash; }
	break;
	case 96:
#line 173 "redis_protocol_parser.rl"
	{_command = command::geopos; }
	break;
	case 97:
#line 174 "redis_protocol_parser.rl"
	{_command = command::georadius; }
	break;
	case 98:
#line 175 "redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
	break;
	case 99:
#line 176 "redis_protocol_parser.rl"
	{_command = command::setbit; }
	break;
	case 100:
#line 177 "redis_protocol_parser.rl"
	{_command = command::getbit; }
	break;
	case 101:
#line 178 "redis_protocol_parser.rl"
	{_command = command::bitcount; }
	break;
	case 102:
#line 179 "redis_protocol_parser.rl"
	{_command = command::bitop; }
	break;
	case 103:
#line 180 "redis_protocol_parser.rl"
	{_command = command::bitfield; }
	break;
	case 104:
#line 181 "redis_protocol_parser.rl"
	{_command = command::bitpos; }
	break;
	case 105:
#line 182 "redis_protocol_parser.rl"
	{_command = command::pfadd; }
	break;
	case 106:
#line 183 "redis_protocol_parser.rl"
	{_command = command::pfcount; }
	break;
	case 107:
#line 184 "redis_protocol_parser.rl"
	{_command = command::pfmerge; }
	break;
	case 108:
#line 196 "redis_protocol_parser.rl"
	{ _arg_size = _u32;}
	break;
	case 109:
#line 198 "redis_protocol_parser.rl"
	{{
    prepush();
{ _fsm_stack[ _fsm_top++] =  _fsm_cs;  _fsm_cs = 363; goto _again;}} }
	break;
	case 110:
#line 198 "redis_protocol_parser.rl"
	{_state = state::ok;}
	break;
#line 1399 "redis_protocol_parser.c"
		}
	}

_again:
	if (  _fsm_cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 346 "redis_protocol_parser.rl"
        if (_state != state::error) {
            return p;
        }
        // error ?
        if (p != pe) {
            p = pe;
            return p;
        }
        return nullptr;
    }
    bool eof() const {
        return _state == state::eof;
    }
};
