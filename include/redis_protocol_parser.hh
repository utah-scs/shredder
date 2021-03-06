
#line 1 "include/redis_protocol_parser.rl"
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


#line 209 "include/redis_protocol_parser.rl"


class redis_protocol_parser : public ragel_parser_base<redis_protocol_parser> {
    
#line 43 "include/redis_protocol_parser.hh"
static const int start = 1;
static const int error = 0;

static const int en_blob = 366;
static const int en_main = 1;


#line 213 "include/redis_protocol_parser.rl"
public:
    enum class state {
        error,
        eof,
        ok,
    };
    enum class command {
        quit,
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
        
#line 181 "include/redis_protocol_parser.hh"
	{
	 _fsm_cs = start;
	 _fsm_top = 0;
	}

#line 342 "include/redis_protocol_parser.rl"
    }

    char* parse(char* p, char* pe, char* eof) {
        sstring_builder::guard g(_builder, p, pe);
        auto str = [this, &g, &p] { g.mark_end(p); return get_str(); };
        
#line 194 "include/redis_protocol_parser.hh"
	{
	if ( p == pe )
		goto _test_eof;
	goto _resume;

_again:
	switch (  _fsm_cs ) {
		case 1: goto st1;
		case 0: goto st0;
		case 2: goto st2;
		case 3: goto st3;
		case 4: goto st4;
		case 5: goto st5;
		case 6: goto st6;
		case 7: goto st7;
		case 8: goto st8;
		case 9: goto st9;
		case 10: goto st10;
		case 11: goto st11;
		case 12: goto st12;
		case 13: goto st13;
		case 14: goto st14;
		case 15: goto st15;
		case 16: goto st16;
		case 17: goto st17;
		case 18: goto st18;
		case 19: goto st19;
		case 20: goto st20;
		case 21: goto st21;
		case 22: goto st22;
		case 367: goto st367;
		case 23: goto st23;
		case 24: goto st24;
		case 25: goto st25;
		case 26: goto st26;
		case 27: goto st27;
		case 28: goto st28;
		case 29: goto st29;
		case 30: goto st30;
		case 31: goto st31;
		case 32: goto st32;
		case 33: goto st33;
		case 34: goto st34;
		case 35: goto st35;
		case 36: goto st36;
		case 37: goto st37;
		case 38: goto st38;
		case 39: goto st39;
		case 40: goto st40;
		case 41: goto st41;
		case 42: goto st42;
		case 43: goto st43;
		case 44: goto st44;
		case 45: goto st45;
		case 46: goto st46;
		case 47: goto st47;
		case 48: goto st48;
		case 49: goto st49;
		case 50: goto st50;
		case 51: goto st51;
		case 52: goto st52;
		case 53: goto st53;
		case 54: goto st54;
		case 55: goto st55;
		case 56: goto st56;
		case 57: goto st57;
		case 58: goto st58;
		case 59: goto st59;
		case 60: goto st60;
		case 61: goto st61;
		case 62: goto st62;
		case 63: goto st63;
		case 64: goto st64;
		case 65: goto st65;
		case 66: goto st66;
		case 67: goto st67;
		case 68: goto st68;
		case 69: goto st69;
		case 70: goto st70;
		case 71: goto st71;
		case 72: goto st72;
		case 73: goto st73;
		case 74: goto st74;
		case 75: goto st75;
		case 76: goto st76;
		case 77: goto st77;
		case 78: goto st78;
		case 79: goto st79;
		case 80: goto st80;
		case 81: goto st81;
		case 82: goto st82;
		case 83: goto st83;
		case 84: goto st84;
		case 85: goto st85;
		case 86: goto st86;
		case 87: goto st87;
		case 88: goto st88;
		case 89: goto st89;
		case 90: goto st90;
		case 91: goto st91;
		case 92: goto st92;
		case 93: goto st93;
		case 94: goto st94;
		case 95: goto st95;
		case 96: goto st96;
		case 97: goto st97;
		case 98: goto st98;
		case 99: goto st99;
		case 100: goto st100;
		case 101: goto st101;
		case 102: goto st102;
		case 103: goto st103;
		case 104: goto st104;
		case 105: goto st105;
		case 106: goto st106;
		case 107: goto st107;
		case 108: goto st108;
		case 109: goto st109;
		case 110: goto st110;
		case 111: goto st111;
		case 112: goto st112;
		case 113: goto st113;
		case 114: goto st114;
		case 115: goto st115;
		case 116: goto st116;
		case 117: goto st117;
		case 118: goto st118;
		case 119: goto st119;
		case 120: goto st120;
		case 121: goto st121;
		case 122: goto st122;
		case 123: goto st123;
		case 124: goto st124;
		case 125: goto st125;
		case 126: goto st126;
		case 127: goto st127;
		case 128: goto st128;
		case 129: goto st129;
		case 130: goto st130;
		case 131: goto st131;
		case 132: goto st132;
		case 133: goto st133;
		case 134: goto st134;
		case 135: goto st135;
		case 136: goto st136;
		case 137: goto st137;
		case 138: goto st138;
		case 139: goto st139;
		case 140: goto st140;
		case 141: goto st141;
		case 142: goto st142;
		case 143: goto st143;
		case 144: goto st144;
		case 145: goto st145;
		case 146: goto st146;
		case 147: goto st147;
		case 148: goto st148;
		case 149: goto st149;
		case 150: goto st150;
		case 151: goto st151;
		case 152: goto st152;
		case 153: goto st153;
		case 154: goto st154;
		case 155: goto st155;
		case 156: goto st156;
		case 157: goto st157;
		case 158: goto st158;
		case 159: goto st159;
		case 160: goto st160;
		case 161: goto st161;
		case 162: goto st162;
		case 163: goto st163;
		case 164: goto st164;
		case 165: goto st165;
		case 166: goto st166;
		case 167: goto st167;
		case 168: goto st168;
		case 169: goto st169;
		case 170: goto st170;
		case 171: goto st171;
		case 172: goto st172;
		case 173: goto st173;
		case 174: goto st174;
		case 175: goto st175;
		case 176: goto st176;
		case 177: goto st177;
		case 178: goto st178;
		case 179: goto st179;
		case 180: goto st180;
		case 181: goto st181;
		case 182: goto st182;
		case 183: goto st183;
		case 184: goto st184;
		case 185: goto st185;
		case 186: goto st186;
		case 187: goto st187;
		case 188: goto st188;
		case 189: goto st189;
		case 190: goto st190;
		case 191: goto st191;
		case 192: goto st192;
		case 193: goto st193;
		case 194: goto st194;
		case 195: goto st195;
		case 196: goto st196;
		case 197: goto st197;
		case 198: goto st198;
		case 199: goto st199;
		case 200: goto st200;
		case 201: goto st201;
		case 202: goto st202;
		case 203: goto st203;
		case 204: goto st204;
		case 205: goto st205;
		case 206: goto st206;
		case 207: goto st207;
		case 208: goto st208;
		case 209: goto st209;
		case 210: goto st210;
		case 211: goto st211;
		case 212: goto st212;
		case 213: goto st213;
		case 214: goto st214;
		case 215: goto st215;
		case 216: goto st216;
		case 217: goto st217;
		case 218: goto st218;
		case 219: goto st219;
		case 220: goto st220;
		case 221: goto st221;
		case 222: goto st222;
		case 223: goto st223;
		case 224: goto st224;
		case 225: goto st225;
		case 226: goto st226;
		case 227: goto st227;
		case 228: goto st228;
		case 229: goto st229;
		case 230: goto st230;
		case 231: goto st231;
		case 232: goto st232;
		case 233: goto st233;
		case 234: goto st234;
		case 235: goto st235;
		case 236: goto st236;
		case 237: goto st237;
		case 238: goto st238;
		case 239: goto st239;
		case 240: goto st240;
		case 241: goto st241;
		case 242: goto st242;
		case 243: goto st243;
		case 244: goto st244;
		case 245: goto st245;
		case 246: goto st246;
		case 247: goto st247;
		case 248: goto st248;
		case 249: goto st249;
		case 250: goto st250;
		case 251: goto st251;
		case 252: goto st252;
		case 253: goto st253;
		case 254: goto st254;
		case 255: goto st255;
		case 256: goto st256;
		case 257: goto st257;
		case 258: goto st258;
		case 259: goto st259;
		case 260: goto st260;
		case 261: goto st261;
		case 262: goto st262;
		case 263: goto st263;
		case 264: goto st264;
		case 265: goto st265;
		case 266: goto st266;
		case 267: goto st267;
		case 268: goto st268;
		case 269: goto st269;
		case 270: goto st270;
		case 271: goto st271;
		case 272: goto st272;
		case 273: goto st273;
		case 274: goto st274;
		case 275: goto st275;
		case 276: goto st276;
		case 277: goto st277;
		case 278: goto st278;
		case 279: goto st279;
		case 280: goto st280;
		case 281: goto st281;
		case 282: goto st282;
		case 283: goto st283;
		case 284: goto st284;
		case 285: goto st285;
		case 286: goto st286;
		case 287: goto st287;
		case 288: goto st288;
		case 289: goto st289;
		case 290: goto st290;
		case 291: goto st291;
		case 292: goto st292;
		case 293: goto st293;
		case 294: goto st294;
		case 295: goto st295;
		case 296: goto st296;
		case 297: goto st297;
		case 298: goto st298;
		case 299: goto st299;
		case 300: goto st300;
		case 301: goto st301;
		case 302: goto st302;
		case 303: goto st303;
		case 304: goto st304;
		case 305: goto st305;
		case 306: goto st306;
		case 307: goto st307;
		case 308: goto st308;
		case 309: goto st309;
		case 310: goto st310;
		case 311: goto st311;
		case 312: goto st312;
		case 313: goto st313;
		case 314: goto st314;
		case 315: goto st315;
		case 316: goto st316;
		case 317: goto st317;
		case 318: goto st318;
		case 319: goto st319;
		case 320: goto st320;
		case 321: goto st321;
		case 322: goto st322;
		case 323: goto st323;
		case 324: goto st324;
		case 325: goto st325;
		case 326: goto st326;
		case 327: goto st327;
		case 328: goto st328;
		case 329: goto st329;
		case 330: goto st330;
		case 331: goto st331;
		case 332: goto st332;
		case 333: goto st333;
		case 334: goto st334;
		case 335: goto st335;
		case 336: goto st336;
		case 337: goto st337;
		case 338: goto st338;
		case 339: goto st339;
		case 340: goto st340;
		case 341: goto st341;
		case 342: goto st342;
		case 343: goto st343;
		case 344: goto st344;
		case 345: goto st345;
		case 346: goto st346;
		case 347: goto st347;
		case 348: goto st348;
		case 349: goto st349;
		case 350: goto st350;
		case 351: goto st351;
		case 352: goto st352;
		case 353: goto st353;
		case 354: goto st354;
		case 355: goto st355;
		case 356: goto st356;
		case 357: goto st357;
		case 358: goto st358;
		case 359: goto st359;
		case 360: goto st360;
		case 361: goto st361;
		case 362: goto st362;
		case 363: goto st363;
		case 364: goto st364;
		case 365: goto st365;
		case 366: goto st366;
		case 368: goto st368;
	default: break;
	}

	if ( ++p == pe )
		goto _test_eof;
_resume:
	switch (  _fsm_cs )
	{
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	if ( (*p) == 42 )
		goto tr0;
	goto st0;
st0:
 _fsm_cs = 0;
	goto _out;
tr0:
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 597 "include/redis_protocol_parser.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr2;
	goto st0;
tr2:
#line 79 "include/redis_protocol_parser.rl"
	{ _u32 = 0;}
#line 79 "include/redis_protocol_parser.rl"
	{ _u32 *= 10; _u32 += (*p) - '0';}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st3;
tr4:
#line 79 "include/redis_protocol_parser.rl"
	{ _u32 *= 10; _u32 += (*p) - '0';}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 619 "include/redis_protocol_parser.hh"
	if ( (*p) == 13 )
		goto tr3;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr4;
	goto st0;
tr3:
#line 80 "include/redis_protocol_parser.rl"
	{_args_count = _u32;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 635 "include/redis_protocol_parser.hh"
	if ( (*p) == 10 )
		goto tr5;
	goto st0;
tr5:
#line 80 "include/redis_protocol_parser.rl"
	{_args_count = _u32;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 649 "include/redis_protocol_parser.hh"
	if ( (*p) == 36 )
		goto tr6;
	goto st0;
tr6:
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 661 "include/redis_protocol_parser.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr7;
	goto st0;
tr7:
#line 79 "include/redis_protocol_parser.rl"
	{ _u32 = 0;}
#line 79 "include/redis_protocol_parser.rl"
	{ _u32 *= 10; _u32 += (*p) - '0';}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st7;
tr9:
#line 79 "include/redis_protocol_parser.rl"
	{ _u32 *= 10; _u32 += (*p) - '0';}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 683 "include/redis_protocol_parser.hh"
	if ( (*p) == 13 )
		goto tr8;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr9;
	goto st0;
tr8:
#line 197 "include/redis_protocol_parser.rl"
	{ _arg_size = _u32;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 699 "include/redis_protocol_parser.hh"
	if ( (*p) == 10 )
		goto tr10;
	goto st0;
tr10:
#line 197 "include/redis_protocol_parser.rl"
	{ _arg_size = _u32;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 713 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr11;
		case 66: goto tr12;
		case 67: goto tr13;
		case 68: goto tr14;
		case 69: goto tr15;
		case 71: goto tr16;
		case 72: goto tr17;
		case 73: goto tr18;
		case 74: goto tr19;
		case 76: goto tr20;
		case 77: goto tr21;
		case 80: goto tr22;
		case 81: goto tr23;
		case 82: goto tr24;
		case 83: goto tr25;
		case 84: goto tr26;
		case 90: goto tr27;
		case 97: goto tr11;
		case 98: goto tr12;
		case 99: goto tr13;
		case 100: goto tr14;
		case 101: goto tr15;
		case 103: goto tr16;
		case 104: goto tr17;
		case 105: goto tr18;
		case 106: goto tr19;
		case 108: goto tr20;
		case 109: goto tr21;
		case 112: goto tr22;
		case 113: goto tr23;
		case 114: goto tr24;
		case 115: goto tr25;
		case 116: goto tr26;
		case 122: goto tr27;
	}
	goto st0;
tr11:
#line 98 "include/redis_protocol_parser.rl"
	{_command = command::append;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 761 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 80: goto tr28;
		case 112: goto tr28;
	}
	goto st0;
tr28:
#line 98 "include/redis_protocol_parser.rl"
	{_command = command::append;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 777 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 80: goto tr29;
		case 112: goto tr29;
	}
	goto st0;
tr29:
#line 98 "include/redis_protocol_parser.rl"
	{_command = command::append;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 793 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr30;
		case 101: goto tr30;
	}
	goto st0;
tr30:
#line 98 "include/redis_protocol_parser.rl"
	{_command = command::append;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 809 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr31;
		case 110: goto tr31;
	}
	goto st0;
tr31:
#line 98 "include/redis_protocol_parser.rl"
	{_command = command::append;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 825 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr32;
		case 100: goto tr32;
	}
	goto st0;
tr32:
#line 98 "include/redis_protocol_parser.rl"
	{_command = command::append;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr64:
#line 96 "include/redis_protocol_parser.rl"
	{_command = command::command;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr176:
#line 84 "include/redis_protocol_parser.rl"
	{_command = command::js;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr249:
#line 82 "include/redis_protocol_parser.rl"
	{_command = command::quit;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr51:
#line 179 "include/redis_protocol_parser.rl"
	{_command = command::bitcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr55:
#line 181 "include/redis_protocol_parser.rl"
	{_command = command::bitfield; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr56:
#line 180 "include/redis_protocol_parser.rl"
	{_command = command::bitop; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr58:
#line 182 "include/redis_protocol_parser.rl"
	{_command = command::bitpos; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr67:
#line 89 "include/redis_protocol_parser.rl"
	{_command = command::del;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr70:
#line 95 "include/redis_protocol_parser.rl"
	{_command = command::decrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr74:
#line 90 "include/redis_protocol_parser.rl"
	{_command = command::echo;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr79:
#line 97 "include/redis_protocol_parser.rl"
	{_command = command::exists;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr82:
#line 141 "include/redis_protocol_parser.rl"
	{_command = command::expire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr92:
#line 171 "include/redis_protocol_parser.rl"
	{_command = command::geoadd; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr95:
#line 172 "include/redis_protocol_parser.rl"
	{_command = command::geodist; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr98:
#line 173 "include/redis_protocol_parser.rl"
	{_command = command::geohash; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr100:
#line 174 "include/redis_protocol_parser.rl"
	{_command = command::geopos; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr113:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr116:
#line 178 "include/redis_protocol_parser.rl"
	{_command = command::getbit; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr127:
#line 115 "include/redis_protocol_parser.rl"
	{_command = command::hdel;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr132:
#line 118 "include/redis_protocol_parser.rl"
	{_command = command::hexists;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr150:
#line 122 "include/redis_protocol_parser.rl"
	{_command = command::hkeys;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr152:
#line 117 "include/redis_protocol_parser.rl"
	{_command = command::hlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr168:
#line 123 "include/redis_protocol_parser.rl"
	{_command = command::hvals;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr137:
#line 125 "include/redis_protocol_parser.rl"
	{_command = command::hgetall;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr147:
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr156:
#line 124 "include/redis_protocol_parser.rl"
	{_command = command::hmget;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr158:
#line 114 "include/redis_protocol_parser.rl"
	{_command = command::hmset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr161:
#line 113 "include/redis_protocol_parser.rl"
	{_command = command::hset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr165:
#line 119 "include/redis_protocol_parser.rl"
	{_command = command::hstrlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr175:
#line 83 "include/redis_protocol_parser.rl"
	{_command = command::info;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr174:
#line 94 "include/redis_protocol_parser.rl"
	{_command = command::incrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr192:
#line 103 "include/redis_protocol_parser.rl"
	{_command = command::llen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr206:
#line 107 "include/redis_protocol_parser.rl"
	{_command = command::lset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr209:
#line 112 "include/redis_protocol_parser.rl"
	{_command = command::ltrim;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr187:
#line 104 "include/redis_protocol_parser.rl"
	{_command = command::lindex;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr190:
#line 105 "include/redis_protocol_parser.rl"
	{_command = command::linsert;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr195:
#line 102 "include/redis_protocol_parser.rl"
	{_command = command::lpop;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr198:
#line 101 "include/redis_protocol_parser.rl"
	{_command = command::lpushx;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr203:
#line 106 "include/redis_protocol_parser.rl"
	{_command = command::lrange;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr204:
#line 111 "include/redis_protocol_parser.rl"
	{_command = command::lrem;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr213:
#line 88 "include/redis_protocol_parser.rl"
	{_command = command::mget;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr215:
#line 86 "include/redis_protocol_parser.rl"
	{_command = command::mset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr244:
#line 91 "include/redis_protocol_parser.rl"
	{_command = command::ping;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr246:
#line 144 "include/redis_protocol_parser.rl"
	{_command = command::pttl; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr225:
#line 145 "include/redis_protocol_parser.rl"
	{_command = command::persist; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr229:
#line 142 "include/redis_protocol_parser.rl"
	{_command = command::pexpire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr234:
#line 183 "include/redis_protocol_parser.rl"
	{_command = command::pfadd; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr238:
#line 184 "include/redis_protocol_parser.rl"
	{_command = command::pfcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr242:
#line 185 "include/redis_protocol_parser.rl"
	{_command = command::pfmerge; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr253:
#line 110 "include/redis_protocol_parser.rl"
	{_command = command::rpop;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr256:
#line 109 "include/redis_protocol_parser.rl"
	{_command = command::rpushx;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr268:
#line 126 "include/redis_protocol_parser.rl"
	{_command = command::sadd;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr271:
#line 127 "include/redis_protocol_parser.rl"
	{_command = command::scard;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr314:
#line 139 "include/redis_protocol_parser.rl"
	{_command = command::spop;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr329:
#line 99 "include/redis_protocol_parser.rl"
	{_command = command::strlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr279:
#line 133 "include/redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr284:
#line 170 "include/redis_protocol_parser.rl"
	{_command = command::select; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr287:
#line 177 "include/redis_protocol_parser.rl"
	{_command = command::setbit; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr303:
#line 128 "include/redis_protocol_parser.rl"
	{_command = command::sismember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr297:
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr310:
#line 129 "include/redis_protocol_parser.rl"
	{_command = command::smembers;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr312:
#line 138 "include/redis_protocol_parser.rl"
	{_command = command::smove;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr324:
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr325:
#line 131 "include/redis_protocol_parser.rl"
	{_command = command::srem;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr338:
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr341:
#line 143 "include/redis_protocol_parser.rl"
	{_command = command::ttl; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr343:
#line 140 "include/redis_protocol_parser.rl"
	{_command = command::type; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr353:
#line 146 "include/redis_protocol_parser.rl"
	{_command = command::zadd; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr368:
#line 161 "include/redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr388:
#line 168 "include/redis_protocol_parser.rl"
	{_command = command::zlexcount;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr357:
#line 147 "include/redis_protocol_parser.rl"
	{_command = command::zcard; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr360:
#line 148 "include/redis_protocol_parser.rl"
	{_command = command::zcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr374:
#line 149 "include/redis_protocol_parser.rl"
	{_command = command::zincrby; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr381:
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr393:
#line 151 "include/redis_protocol_parser.rl"
	{_command = command::zrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr400:
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr404:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr418:
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr421:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr425:
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr430:
#line 157 "include/redis_protocol_parser.rl"
	{_command = command::zrevrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr438:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr442:
#line 165 "include/redis_protocol_parser.rl"
	{_command = command::zscan; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr444:
#line 158 "include/redis_protocol_parser.rl"
	{_command = command::zscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
tr453:
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 1351 "include/redis_protocol_parser.hh"
	if ( (*p) == 13 )
		goto tr33;
	goto st0;
tr33:
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 1363 "include/redis_protocol_parser.hh"
	if ( (*p) == 10 )
		goto tr34;
	goto st0;
tr34:
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 1375 "include/redis_protocol_parser.hh"
	if ( (*p) == 36 )
		goto tr35;
	goto st0;
tr35:
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 1387 "include/redis_protocol_parser.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr36;
	goto st0;
tr36:
#line 79 "include/redis_protocol_parser.rl"
	{ _u32 = 0;}
#line 79 "include/redis_protocol_parser.rl"
	{ _u32 *= 10; _u32 += (*p) - '0';}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st19;
tr38:
#line 79 "include/redis_protocol_parser.rl"
	{ _u32 *= 10; _u32 += (*p) - '0';}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 1409 "include/redis_protocol_parser.hh"
	if ( (*p) == 13 )
		goto tr37;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr38;
	goto st0;
tr37:
#line 197 "include/redis_protocol_parser.rl"
	{ _arg_size = _u32;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 1425 "include/redis_protocol_parser.hh"
	if ( (*p) == 10 )
		goto tr39;
	goto st0;
tr39:
#line 197 "include/redis_protocol_parser.rl"
	{ _arg_size = _u32;}
#line 199 "include/redis_protocol_parser.rl"
	{{
    prepush();
{ _fsm_stack[ _fsm_top++] = 21; goto st366;}} }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 1443 "include/redis_protocol_parser.hh"
	if ( (*p) == 13 )
		goto tr40;
	goto st0;
tr40:
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 1455 "include/redis_protocol_parser.hh"
	if ( (*p) == 10 )
		goto tr41;
	goto st0;
tr41:
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st367;
st367:
	if ( ++p == pe )
		goto _test_eof367;
case 367:
#line 1467 "include/redis_protocol_parser.hh"
	if ( (*p) == 36 )
		goto tr35;
	goto st0;
tr12:
#line 179 "include/redis_protocol_parser.rl"
	{_command = command::bitcount; }
#line 182 "include/redis_protocol_parser.rl"
	{_command = command::bitpos; }
#line 180 "include/redis_protocol_parser.rl"
	{_command = command::bitop; }
#line 181 "include/redis_protocol_parser.rl"
	{_command = command::bitfield; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
#line 1487 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr42;
		case 105: goto tr42;
	}
	goto st0;
tr42:
#line 179 "include/redis_protocol_parser.rl"
	{_command = command::bitcount; }
#line 182 "include/redis_protocol_parser.rl"
	{_command = command::bitpos; }
#line 180 "include/redis_protocol_parser.rl"
	{_command = command::bitop; }
#line 181 "include/redis_protocol_parser.rl"
	{_command = command::bitfield; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 1509 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr43;
		case 116: goto tr43;
	}
	goto st0;
tr43:
#line 179 "include/redis_protocol_parser.rl"
	{_command = command::bitcount; }
#line 182 "include/redis_protocol_parser.rl"
	{_command = command::bitpos; }
#line 180 "include/redis_protocol_parser.rl"
	{_command = command::bitop; }
#line 181 "include/redis_protocol_parser.rl"
	{_command = command::bitfield; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 1531 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr44;
		case 70: goto tr45;
		case 79: goto tr46;
		case 80: goto tr47;
		case 99: goto tr44;
		case 102: goto tr45;
		case 111: goto tr46;
		case 112: goto tr47;
	}
	goto st0;
tr44:
#line 179 "include/redis_protocol_parser.rl"
	{_command = command::bitcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st26;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 1553 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr48;
		case 111: goto tr48;
	}
	goto st0;
tr48:
#line 179 "include/redis_protocol_parser.rl"
	{_command = command::bitcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st27;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
#line 1569 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 85: goto tr49;
		case 117: goto tr49;
	}
	goto st0;
tr49:
#line 179 "include/redis_protocol_parser.rl"
	{_command = command::bitcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
#line 1585 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr50;
		case 110: goto tr50;
	}
	goto st0;
tr50:
#line 179 "include/redis_protocol_parser.rl"
	{_command = command::bitcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
#line 1601 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr51;
		case 116: goto tr51;
	}
	goto st0;
tr45:
#line 181 "include/redis_protocol_parser.rl"
	{_command = command::bitfield; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 1617 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr52;
		case 105: goto tr52;
	}
	goto st0;
tr52:
#line 181 "include/redis_protocol_parser.rl"
	{_command = command::bitfield; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st31;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
#line 1633 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr53;
		case 101: goto tr53;
	}
	goto st0;
tr53:
#line 181 "include/redis_protocol_parser.rl"
	{_command = command::bitfield; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st32;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
#line 1649 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr54;
		case 108: goto tr54;
	}
	goto st0;
tr54:
#line 181 "include/redis_protocol_parser.rl"
	{_command = command::bitfield; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st33;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
#line 1665 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr55;
		case 100: goto tr55;
	}
	goto st0;
tr46:
#line 180 "include/redis_protocol_parser.rl"
	{_command = command::bitop; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st34;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
#line 1681 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 80: goto tr56;
		case 112: goto tr56;
	}
	goto st0;
tr47:
#line 182 "include/redis_protocol_parser.rl"
	{_command = command::bitpos; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st35;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
#line 1697 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr57;
		case 111: goto tr57;
	}
	goto st0;
tr57:
#line 182 "include/redis_protocol_parser.rl"
	{_command = command::bitpos; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 1713 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr58;
		case 115: goto tr58;
	}
	goto st0;
tr13:
#line 96 "include/redis_protocol_parser.rl"
	{_command = command::command;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st37;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
#line 1729 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr59;
		case 111: goto tr59;
	}
	goto st0;
tr59:
#line 96 "include/redis_protocol_parser.rl"
	{_command = command::command;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st38;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
#line 1745 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr60;
		case 109: goto tr60;
	}
	goto st0;
tr60:
#line 96 "include/redis_protocol_parser.rl"
	{_command = command::command;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st39;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
#line 1761 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr61;
		case 109: goto tr61;
	}
	goto st0;
tr61:
#line 96 "include/redis_protocol_parser.rl"
	{_command = command::command;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st40;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
#line 1777 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr62;
		case 97: goto tr62;
	}
	goto st0;
tr62:
#line 96 "include/redis_protocol_parser.rl"
	{_command = command::command;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st41;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
#line 1793 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr63;
		case 110: goto tr63;
	}
	goto st0;
tr63:
#line 96 "include/redis_protocol_parser.rl"
	{_command = command::command;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st42;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
#line 1809 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr64;
		case 100: goto tr64;
	}
	goto st0;
tr14:
#line 89 "include/redis_protocol_parser.rl"
	{_command = command::del;}
#line 93 "include/redis_protocol_parser.rl"
	{_command = command::decr;}
#line 95 "include/redis_protocol_parser.rl"
	{_command = command::decrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st43;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
#line 1829 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr65;
		case 101: goto tr65;
	}
	goto st0;
tr65:
#line 89 "include/redis_protocol_parser.rl"
	{_command = command::del;}
#line 93 "include/redis_protocol_parser.rl"
	{_command = command::decr;}
#line 95 "include/redis_protocol_parser.rl"
	{_command = command::decrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st44;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
#line 1849 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr66;
		case 76: goto tr67;
		case 99: goto tr66;
		case 108: goto tr67;
	}
	goto st0;
tr66:
#line 93 "include/redis_protocol_parser.rl"
	{_command = command::decr;}
#line 95 "include/redis_protocol_parser.rl"
	{_command = command::decrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st45;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
#line 1869 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr68;
		case 114: goto tr68;
	}
	goto st0;
tr68:
#line 93 "include/redis_protocol_parser.rl"
	{_command = command::decr;}
#line 95 "include/redis_protocol_parser.rl"
	{_command = command::decrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st46;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
#line 1887 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 66: goto tr69;
		case 98: goto tr69;
	}
	goto st0;
tr69:
#line 95 "include/redis_protocol_parser.rl"
	{_command = command::decrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st47;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
#line 1904 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 89: goto tr70;
		case 121: goto tr70;
	}
	goto st0;
tr15:
#line 90 "include/redis_protocol_parser.rl"
	{_command = command::echo;}
#line 97 "include/redis_protocol_parser.rl"
	{_command = command::exists;}
#line 141 "include/redis_protocol_parser.rl"
	{_command = command::expire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st48;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
#line 1924 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr71;
		case 88: goto tr72;
		case 99: goto tr71;
		case 120: goto tr72;
	}
	goto st0;
tr71:
#line 90 "include/redis_protocol_parser.rl"
	{_command = command::echo;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st49;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
#line 1942 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 72: goto tr73;
		case 104: goto tr73;
	}
	goto st0;
tr73:
#line 90 "include/redis_protocol_parser.rl"
	{_command = command::echo;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st50;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
#line 1958 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr74;
		case 111: goto tr74;
	}
	goto st0;
tr72:
#line 97 "include/redis_protocol_parser.rl"
	{_command = command::exists;}
#line 141 "include/redis_protocol_parser.rl"
	{_command = command::expire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st51;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
#line 1976 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr75;
		case 80: goto tr76;
		case 105: goto tr75;
		case 112: goto tr76;
	}
	goto st0;
tr75:
#line 97 "include/redis_protocol_parser.rl"
	{_command = command::exists;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st52;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
#line 1994 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr77;
		case 115: goto tr77;
	}
	goto st0;
tr77:
#line 97 "include/redis_protocol_parser.rl"
	{_command = command::exists;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st53;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
#line 2010 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr78;
		case 116: goto tr78;
	}
	goto st0;
tr78:
#line 97 "include/redis_protocol_parser.rl"
	{_command = command::exists;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st54;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
#line 2026 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr79;
		case 115: goto tr79;
	}
	goto st0;
tr76:
#line 141 "include/redis_protocol_parser.rl"
	{_command = command::expire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st55;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
#line 2042 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr80;
		case 105: goto tr80;
	}
	goto st0;
tr80:
#line 141 "include/redis_protocol_parser.rl"
	{_command = command::expire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st56;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
#line 2058 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr81;
		case 114: goto tr81;
	}
	goto st0;
tr81:
#line 141 "include/redis_protocol_parser.rl"
	{_command = command::expire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st57;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
#line 2074 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr82;
		case 101: goto tr82;
	}
	goto st0;
tr16:
#line 178 "include/redis_protocol_parser.rl"
	{_command = command::getbit; }
#line 87 "include/redis_protocol_parser.rl"
	{_command = command::get;}
#line 171 "include/redis_protocol_parser.rl"
	{_command = command::geoadd; }
#line 172 "include/redis_protocol_parser.rl"
	{_command = command::geodist; }
#line 173 "include/redis_protocol_parser.rl"
	{_command = command::geohash; }
#line 174 "include/redis_protocol_parser.rl"
	{_command = command::geopos; }
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 175 "include/redis_protocol_parser.rl"
	{_command = command::georadius; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st58;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
#line 2104 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr83;
		case 101: goto tr83;
	}
	goto st0;
tr83:
#line 178 "include/redis_protocol_parser.rl"
	{_command = command::getbit; }
#line 87 "include/redis_protocol_parser.rl"
	{_command = command::get;}
#line 171 "include/redis_protocol_parser.rl"
	{_command = command::geoadd; }
#line 172 "include/redis_protocol_parser.rl"
	{_command = command::geodist; }
#line 173 "include/redis_protocol_parser.rl"
	{_command = command::geohash; }
#line 174 "include/redis_protocol_parser.rl"
	{_command = command::geopos; }
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 175 "include/redis_protocol_parser.rl"
	{_command = command::georadius; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st59;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
#line 2134 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr84;
		case 84: goto tr85;
		case 111: goto tr84;
		case 116: goto tr85;
	}
	goto st0;
tr84:
#line 171 "include/redis_protocol_parser.rl"
	{_command = command::geoadd; }
#line 172 "include/redis_protocol_parser.rl"
	{_command = command::geodist; }
#line 173 "include/redis_protocol_parser.rl"
	{_command = command::geohash; }
#line 174 "include/redis_protocol_parser.rl"
	{_command = command::geopos; }
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 175 "include/redis_protocol_parser.rl"
	{_command = command::georadius; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st60;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
#line 2162 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr86;
		case 68: goto tr87;
		case 72: goto tr88;
		case 80: goto tr89;
		case 82: goto tr90;
		case 97: goto tr86;
		case 100: goto tr87;
		case 104: goto tr88;
		case 112: goto tr89;
		case 114: goto tr90;
	}
	goto st0;
tr86:
#line 171 "include/redis_protocol_parser.rl"
	{_command = command::geoadd; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st61;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
#line 2186 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr91;
		case 100: goto tr91;
	}
	goto st0;
tr91:
#line 171 "include/redis_protocol_parser.rl"
	{_command = command::geoadd; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st62;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
#line 2202 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr92;
		case 100: goto tr92;
	}
	goto st0;
tr87:
#line 172 "include/redis_protocol_parser.rl"
	{_command = command::geodist; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st63;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
#line 2218 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr93;
		case 105: goto tr93;
	}
	goto st0;
tr93:
#line 172 "include/redis_protocol_parser.rl"
	{_command = command::geodist; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st64;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
#line 2234 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr94;
		case 115: goto tr94;
	}
	goto st0;
tr94:
#line 172 "include/redis_protocol_parser.rl"
	{_command = command::geodist; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st65;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
#line 2250 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr95;
		case 116: goto tr95;
	}
	goto st0;
tr88:
#line 173 "include/redis_protocol_parser.rl"
	{_command = command::geohash; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st66;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
#line 2266 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr96;
		case 97: goto tr96;
	}
	goto st0;
tr96:
#line 173 "include/redis_protocol_parser.rl"
	{_command = command::geohash; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st67;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
#line 2282 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr97;
		case 115: goto tr97;
	}
	goto st0;
tr97:
#line 173 "include/redis_protocol_parser.rl"
	{_command = command::geohash; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st68;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
#line 2298 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 72: goto tr98;
		case 104: goto tr98;
	}
	goto st0;
tr89:
#line 174 "include/redis_protocol_parser.rl"
	{_command = command::geopos; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st69;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
#line 2314 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr99;
		case 111: goto tr99;
	}
	goto st0;
tr99:
#line 174 "include/redis_protocol_parser.rl"
	{_command = command::geopos; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st70;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
#line 2330 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr100;
		case 115: goto tr100;
	}
	goto st0;
tr90:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 175 "include/redis_protocol_parser.rl"
	{_command = command::georadius; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st71;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
#line 2348 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr101;
		case 97: goto tr101;
	}
	goto st0;
tr101:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 175 "include/redis_protocol_parser.rl"
	{_command = command::georadius; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st72;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
#line 2366 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr102;
		case 100: goto tr102;
	}
	goto st0;
tr102:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 175 "include/redis_protocol_parser.rl"
	{_command = command::georadius; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st73;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
#line 2384 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr103;
		case 105: goto tr103;
	}
	goto st0;
tr103:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 175 "include/redis_protocol_parser.rl"
	{_command = command::georadius; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st74;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
#line 2402 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 85: goto tr104;
		case 117: goto tr104;
	}
	goto st0;
tr104:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 175 "include/redis_protocol_parser.rl"
	{_command = command::georadius; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st75;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
#line 2420 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr105;
		case 115: goto tr105;
	}
	goto st0;
tr105:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 175 "include/redis_protocol_parser.rl"
	{_command = command::georadius; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st76;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
#line 2438 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 66: goto tr106;
		case 98: goto tr106;
	}
	goto st0;
tr106:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st77;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
#line 2455 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 89: goto tr107;
		case 121: goto tr107;
	}
	goto st0;
tr107:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st78;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
#line 2471 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr108;
		case 109: goto tr108;
	}
	goto st0;
tr108:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st79;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
#line 2487 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr109;
		case 101: goto tr109;
	}
	goto st0;
tr109:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st80;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
#line 2503 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr110;
		case 109: goto tr110;
	}
	goto st0;
tr110:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st81;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
#line 2519 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 66: goto tr111;
		case 98: goto tr111;
	}
	goto st0;
tr111:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st82;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
#line 2535 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr112;
		case 101: goto tr112;
	}
	goto st0;
tr112:
#line 176 "include/redis_protocol_parser.rl"
	{_command = command::georadiusbymember; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st83;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
#line 2551 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr113;
		case 114: goto tr113;
	}
	goto st0;
tr85:
#line 178 "include/redis_protocol_parser.rl"
	{_command = command::getbit; }
#line 87 "include/redis_protocol_parser.rl"
	{_command = command::get;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st84;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
#line 2569 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 66: goto tr114;
		case 98: goto tr114;
	}
	goto st0;
tr114:
#line 178 "include/redis_protocol_parser.rl"
	{_command = command::getbit; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st85;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
#line 2586 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr115;
		case 105: goto tr115;
	}
	goto st0;
tr115:
#line 178 "include/redis_protocol_parser.rl"
	{_command = command::getbit; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st86;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
#line 2602 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr116;
		case 116: goto tr116;
	}
	goto st0;
tr17:
#line 113 "include/redis_protocol_parser.rl"
	{_command = command::hset;}
#line 125 "include/redis_protocol_parser.rl"
	{_command = command::hgetall;}
#line 116 "include/redis_protocol_parser.rl"
	{_command = command::hget;}
#line 115 "include/redis_protocol_parser.rl"
	{_command = command::hdel;}
#line 117 "include/redis_protocol_parser.rl"
	{_command = command::hlen;}
#line 118 "include/redis_protocol_parser.rl"
	{_command = command::hexists;}
#line 119 "include/redis_protocol_parser.rl"
	{_command = command::hstrlen;}
#line 120 "include/redis_protocol_parser.rl"
	{_command = command::hincrby;}
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 122 "include/redis_protocol_parser.rl"
	{_command = command::hkeys;}
#line 123 "include/redis_protocol_parser.rl"
	{_command = command::hvals;}
#line 124 "include/redis_protocol_parser.rl"
	{_command = command::hmget;}
#line 114 "include/redis_protocol_parser.rl"
	{_command = command::hmset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st87;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
#line 2642 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr117;
		case 69: goto tr118;
		case 71: goto tr119;
		case 73: goto tr120;
		case 75: goto tr121;
		case 76: goto tr122;
		case 77: goto tr123;
		case 83: goto tr124;
		case 86: goto tr125;
		case 100: goto tr117;
		case 101: goto tr118;
		case 103: goto tr119;
		case 105: goto tr120;
		case 107: goto tr121;
		case 108: goto tr122;
		case 109: goto tr123;
		case 115: goto tr124;
		case 118: goto tr125;
	}
	goto st0;
tr117:
#line 115 "include/redis_protocol_parser.rl"
	{_command = command::hdel;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st88;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
#line 2674 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr126;
		case 101: goto tr126;
	}
	goto st0;
tr126:
#line 115 "include/redis_protocol_parser.rl"
	{_command = command::hdel;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st89;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
#line 2690 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr127;
		case 108: goto tr127;
	}
	goto st0;
tr118:
#line 118 "include/redis_protocol_parser.rl"
	{_command = command::hexists;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st90;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
#line 2706 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 88: goto tr128;
		case 120: goto tr128;
	}
	goto st0;
tr128:
#line 118 "include/redis_protocol_parser.rl"
	{_command = command::hexists;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st91;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
#line 2722 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr129;
		case 105: goto tr129;
	}
	goto st0;
tr129:
#line 118 "include/redis_protocol_parser.rl"
	{_command = command::hexists;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st92;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
#line 2738 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr130;
		case 115: goto tr130;
	}
	goto st0;
tr130:
#line 118 "include/redis_protocol_parser.rl"
	{_command = command::hexists;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st93;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
#line 2754 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr131;
		case 116: goto tr131;
	}
	goto st0;
tr131:
#line 118 "include/redis_protocol_parser.rl"
	{_command = command::hexists;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st94;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
#line 2770 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr132;
		case 115: goto tr132;
	}
	goto st0;
tr119:
#line 125 "include/redis_protocol_parser.rl"
	{_command = command::hgetall;}
#line 116 "include/redis_protocol_parser.rl"
	{_command = command::hget;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st95;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
#line 2788 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr133;
		case 101: goto tr133;
	}
	goto st0;
tr133:
#line 125 "include/redis_protocol_parser.rl"
	{_command = command::hgetall;}
#line 116 "include/redis_protocol_parser.rl"
	{_command = command::hget;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st96;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
#line 2806 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr134;
		case 116: goto tr134;
	}
	goto st0;
tr134:
#line 125 "include/redis_protocol_parser.rl"
	{_command = command::hgetall;}
#line 116 "include/redis_protocol_parser.rl"
	{_command = command::hget;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st97;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
#line 2824 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 65: goto tr135;
		case 97: goto tr135;
	}
	goto st0;
tr135:
#line 125 "include/redis_protocol_parser.rl"
	{_command = command::hgetall;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st98;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
#line 2841 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr136;
		case 108: goto tr136;
	}
	goto st0;
tr136:
#line 125 "include/redis_protocol_parser.rl"
	{_command = command::hgetall;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st99;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
#line 2857 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr137;
		case 108: goto tr137;
	}
	goto st0;
tr120:
#line 120 "include/redis_protocol_parser.rl"
	{_command = command::hincrby;}
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st100;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
#line 2875 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr138;
		case 110: goto tr138;
	}
	goto st0;
tr138:
#line 120 "include/redis_protocol_parser.rl"
	{_command = command::hincrby;}
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st101;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
#line 2893 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr139;
		case 99: goto tr139;
	}
	goto st0;
tr139:
#line 120 "include/redis_protocol_parser.rl"
	{_command = command::hincrby;}
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st102;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
#line 2911 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr140;
		case 114: goto tr140;
	}
	goto st0;
tr140:
#line 120 "include/redis_protocol_parser.rl"
	{_command = command::hincrby;}
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st103;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
#line 2929 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 66: goto tr141;
		case 98: goto tr141;
	}
	goto st0;
tr141:
#line 120 "include/redis_protocol_parser.rl"
	{_command = command::hincrby;}
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st104;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
#line 2947 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 89: goto tr142;
		case 121: goto tr142;
	}
	goto st0;
tr142:
#line 120 "include/redis_protocol_parser.rl"
	{_command = command::hincrby;}
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st105;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
#line 2965 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 70: goto tr143;
		case 102: goto tr143;
	}
	goto st0;
tr143:
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st106;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
#line 2982 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr144;
		case 108: goto tr144;
	}
	goto st0;
tr144:
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st107;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
#line 2998 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr145;
		case 111: goto tr145;
	}
	goto st0;
tr145:
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st108;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
#line 3014 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr146;
		case 97: goto tr146;
	}
	goto st0;
tr146:
#line 121 "include/redis_protocol_parser.rl"
	{_command = command::hincrbyfloat;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st109;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
#line 3030 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr147;
		case 116: goto tr147;
	}
	goto st0;
tr121:
#line 122 "include/redis_protocol_parser.rl"
	{_command = command::hkeys;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st110;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
#line 3046 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr148;
		case 101: goto tr148;
	}
	goto st0;
tr148:
#line 122 "include/redis_protocol_parser.rl"
	{_command = command::hkeys;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st111;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
#line 3062 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 89: goto tr149;
		case 121: goto tr149;
	}
	goto st0;
tr149:
#line 122 "include/redis_protocol_parser.rl"
	{_command = command::hkeys;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st112;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
#line 3078 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr150;
		case 115: goto tr150;
	}
	goto st0;
tr122:
#line 117 "include/redis_protocol_parser.rl"
	{_command = command::hlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st113;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
#line 3094 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr151;
		case 101: goto tr151;
	}
	goto st0;
tr151:
#line 117 "include/redis_protocol_parser.rl"
	{_command = command::hlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st114;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
#line 3110 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr152;
		case 110: goto tr152;
	}
	goto st0;
tr123:
#line 124 "include/redis_protocol_parser.rl"
	{_command = command::hmget;}
#line 114 "include/redis_protocol_parser.rl"
	{_command = command::hmset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st115;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
#line 3128 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 71: goto tr153;
		case 83: goto tr154;
		case 103: goto tr153;
		case 115: goto tr154;
	}
	goto st0;
tr153:
#line 124 "include/redis_protocol_parser.rl"
	{_command = command::hmget;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st116;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
#line 3146 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr155;
		case 101: goto tr155;
	}
	goto st0;
tr155:
#line 124 "include/redis_protocol_parser.rl"
	{_command = command::hmget;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st117;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
#line 3162 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr156;
		case 116: goto tr156;
	}
	goto st0;
tr154:
#line 114 "include/redis_protocol_parser.rl"
	{_command = command::hmset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st118;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
#line 3178 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr157;
		case 101: goto tr157;
	}
	goto st0;
tr157:
#line 114 "include/redis_protocol_parser.rl"
	{_command = command::hmset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st119;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
#line 3194 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr158;
		case 116: goto tr158;
	}
	goto st0;
tr124:
#line 113 "include/redis_protocol_parser.rl"
	{_command = command::hset;}
#line 119 "include/redis_protocol_parser.rl"
	{_command = command::hstrlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st120;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
#line 3212 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr159;
		case 84: goto tr160;
		case 101: goto tr159;
		case 116: goto tr160;
	}
	goto st0;
tr159:
#line 113 "include/redis_protocol_parser.rl"
	{_command = command::hset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st121;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
#line 3230 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr161;
		case 116: goto tr161;
	}
	goto st0;
tr160:
#line 119 "include/redis_protocol_parser.rl"
	{_command = command::hstrlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st122;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
#line 3246 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr162;
		case 114: goto tr162;
	}
	goto st0;
tr162:
#line 119 "include/redis_protocol_parser.rl"
	{_command = command::hstrlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st123;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
#line 3262 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr163;
		case 108: goto tr163;
	}
	goto st0;
tr163:
#line 119 "include/redis_protocol_parser.rl"
	{_command = command::hstrlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st124;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
#line 3278 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr164;
		case 101: goto tr164;
	}
	goto st0;
tr164:
#line 119 "include/redis_protocol_parser.rl"
	{_command = command::hstrlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st125;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
#line 3294 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr165;
		case 110: goto tr165;
	}
	goto st0;
tr125:
#line 123 "include/redis_protocol_parser.rl"
	{_command = command::hvals;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st126;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
#line 3310 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr166;
		case 97: goto tr166;
	}
	goto st0;
tr166:
#line 123 "include/redis_protocol_parser.rl"
	{_command = command::hvals;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st127;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
#line 3326 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr167;
		case 108: goto tr167;
	}
	goto st0;
tr167:
#line 123 "include/redis_protocol_parser.rl"
	{_command = command::hvals;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st128;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
#line 3342 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr168;
		case 115: goto tr168;
	}
	goto st0;
tr18:
#line 83 "include/redis_protocol_parser.rl"
	{_command = command::info;}
#line 92 "include/redis_protocol_parser.rl"
	{_command = command::incr;}
#line 94 "include/redis_protocol_parser.rl"
	{_command = command::incrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st129;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
#line 3362 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr169;
		case 110: goto tr169;
	}
	goto st0;
tr169:
#line 83 "include/redis_protocol_parser.rl"
	{_command = command::info;}
#line 92 "include/redis_protocol_parser.rl"
	{_command = command::incr;}
#line 94 "include/redis_protocol_parser.rl"
	{_command = command::incrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st130;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
#line 3382 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr170;
		case 70: goto tr171;
		case 99: goto tr170;
		case 102: goto tr171;
	}
	goto st0;
tr170:
#line 92 "include/redis_protocol_parser.rl"
	{_command = command::incr;}
#line 94 "include/redis_protocol_parser.rl"
	{_command = command::incrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st131;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
#line 3402 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr172;
		case 114: goto tr172;
	}
	goto st0;
tr172:
#line 92 "include/redis_protocol_parser.rl"
	{_command = command::incr;}
#line 94 "include/redis_protocol_parser.rl"
	{_command = command::incrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st132;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
#line 3420 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 66: goto tr173;
		case 98: goto tr173;
	}
	goto st0;
tr173:
#line 94 "include/redis_protocol_parser.rl"
	{_command = command::incrby;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st133;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
#line 3437 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 89: goto tr174;
		case 121: goto tr174;
	}
	goto st0;
tr171:
#line 83 "include/redis_protocol_parser.rl"
	{_command = command::info;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st134;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
#line 3453 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr175;
		case 111: goto tr175;
	}
	goto st0;
tr19:
#line 84 "include/redis_protocol_parser.rl"
	{_command = command::js;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st135;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
#line 3469 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr176;
		case 115: goto tr176;
	}
	goto st0;
tr20:
#line 101 "include/redis_protocol_parser.rl"
	{_command = command::lpushx;}
#line 100 "include/redis_protocol_parser.rl"
	{_command = command::lpush;}
#line 102 "include/redis_protocol_parser.rl"
	{_command = command::lpop;}
#line 103 "include/redis_protocol_parser.rl"
	{_command = command::llen;}
#line 104 "include/redis_protocol_parser.rl"
	{_command = command::lindex;}
#line 105 "include/redis_protocol_parser.rl"
	{_command = command::linsert;}
#line 106 "include/redis_protocol_parser.rl"
	{_command = command::lrange;}
#line 107 "include/redis_protocol_parser.rl"
	{_command = command::lset;}
#line 111 "include/redis_protocol_parser.rl"
	{_command = command::lrem;}
#line 112 "include/redis_protocol_parser.rl"
	{_command = command::ltrim;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st136;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
#line 3503 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr177;
		case 76: goto tr178;
		case 80: goto tr179;
		case 82: goto tr180;
		case 83: goto tr181;
		case 84: goto tr182;
		case 105: goto tr177;
		case 108: goto tr178;
		case 112: goto tr179;
		case 114: goto tr180;
		case 115: goto tr181;
		case 116: goto tr182;
	}
	goto st0;
tr177:
#line 104 "include/redis_protocol_parser.rl"
	{_command = command::lindex;}
#line 105 "include/redis_protocol_parser.rl"
	{_command = command::linsert;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st137;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
#line 3531 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr183;
		case 110: goto tr183;
	}
	goto st0;
tr183:
#line 104 "include/redis_protocol_parser.rl"
	{_command = command::lindex;}
#line 105 "include/redis_protocol_parser.rl"
	{_command = command::linsert;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st138;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
#line 3549 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr184;
		case 83: goto tr185;
		case 100: goto tr184;
		case 115: goto tr185;
	}
	goto st0;
tr184:
#line 104 "include/redis_protocol_parser.rl"
	{_command = command::lindex;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st139;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
#line 3567 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr186;
		case 101: goto tr186;
	}
	goto st0;
tr186:
#line 104 "include/redis_protocol_parser.rl"
	{_command = command::lindex;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st140;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
#line 3583 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 88: goto tr187;
		case 120: goto tr187;
	}
	goto st0;
tr185:
#line 105 "include/redis_protocol_parser.rl"
	{_command = command::linsert;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st141;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
#line 3599 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr188;
		case 101: goto tr188;
	}
	goto st0;
tr188:
#line 105 "include/redis_protocol_parser.rl"
	{_command = command::linsert;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st142;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
#line 3615 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr189;
		case 114: goto tr189;
	}
	goto st0;
tr189:
#line 105 "include/redis_protocol_parser.rl"
	{_command = command::linsert;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st143;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
#line 3631 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr190;
		case 116: goto tr190;
	}
	goto st0;
tr178:
#line 103 "include/redis_protocol_parser.rl"
	{_command = command::llen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st144;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
#line 3647 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr191;
		case 101: goto tr191;
	}
	goto st0;
tr191:
#line 103 "include/redis_protocol_parser.rl"
	{_command = command::llen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st145;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
#line 3663 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr192;
		case 110: goto tr192;
	}
	goto st0;
tr179:
#line 101 "include/redis_protocol_parser.rl"
	{_command = command::lpushx;}
#line 100 "include/redis_protocol_parser.rl"
	{_command = command::lpush;}
#line 102 "include/redis_protocol_parser.rl"
	{_command = command::lpop;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st146;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
#line 3683 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr193;
		case 85: goto tr194;
		case 111: goto tr193;
		case 117: goto tr194;
	}
	goto st0;
tr193:
#line 102 "include/redis_protocol_parser.rl"
	{_command = command::lpop;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st147;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
#line 3701 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 80: goto tr195;
		case 112: goto tr195;
	}
	goto st0;
tr194:
#line 101 "include/redis_protocol_parser.rl"
	{_command = command::lpushx;}
#line 100 "include/redis_protocol_parser.rl"
	{_command = command::lpush;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st148;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
#line 3719 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr196;
		case 115: goto tr196;
	}
	goto st0;
tr196:
#line 101 "include/redis_protocol_parser.rl"
	{_command = command::lpushx;}
#line 100 "include/redis_protocol_parser.rl"
	{_command = command::lpush;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st149;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
#line 3737 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 72: goto tr197;
		case 104: goto tr197;
	}
	goto st0;
tr197:
#line 101 "include/redis_protocol_parser.rl"
	{_command = command::lpushx;}
#line 100 "include/redis_protocol_parser.rl"
	{_command = command::lpush;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st150;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
#line 3755 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 88: goto tr198;
		case 120: goto tr198;
	}
	goto st0;
tr180:
#line 106 "include/redis_protocol_parser.rl"
	{_command = command::lrange;}
#line 111 "include/redis_protocol_parser.rl"
	{_command = command::lrem;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st151;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
#line 3774 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr199;
		case 69: goto tr200;
		case 97: goto tr199;
		case 101: goto tr200;
	}
	goto st0;
tr199:
#line 106 "include/redis_protocol_parser.rl"
	{_command = command::lrange;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st152;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
#line 3792 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr201;
		case 110: goto tr201;
	}
	goto st0;
tr201:
#line 106 "include/redis_protocol_parser.rl"
	{_command = command::lrange;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st153;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
#line 3808 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 71: goto tr202;
		case 103: goto tr202;
	}
	goto st0;
tr202:
#line 106 "include/redis_protocol_parser.rl"
	{_command = command::lrange;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st154;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
#line 3824 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr203;
		case 101: goto tr203;
	}
	goto st0;
tr200:
#line 111 "include/redis_protocol_parser.rl"
	{_command = command::lrem;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st155;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
#line 3840 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr204;
		case 109: goto tr204;
	}
	goto st0;
tr181:
#line 107 "include/redis_protocol_parser.rl"
	{_command = command::lset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st156;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
#line 3856 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr205;
		case 101: goto tr205;
	}
	goto st0;
tr205:
#line 107 "include/redis_protocol_parser.rl"
	{_command = command::lset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st157;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
#line 3872 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr206;
		case 116: goto tr206;
	}
	goto st0;
tr182:
#line 112 "include/redis_protocol_parser.rl"
	{_command = command::ltrim;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st158;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
#line 3888 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr207;
		case 114: goto tr207;
	}
	goto st0;
tr207:
#line 112 "include/redis_protocol_parser.rl"
	{_command = command::ltrim;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st159;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
#line 3904 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr208;
		case 105: goto tr208;
	}
	goto st0;
tr208:
#line 112 "include/redis_protocol_parser.rl"
	{_command = command::ltrim;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st160;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
#line 3920 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr209;
		case 109: goto tr209;
	}
	goto st0;
tr21:
#line 88 "include/redis_protocol_parser.rl"
	{_command = command::mget;}
#line 86 "include/redis_protocol_parser.rl"
	{_command = command::mset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st161;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
#line 3938 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 71: goto tr210;
		case 83: goto tr211;
		case 103: goto tr210;
		case 115: goto tr211;
	}
	goto st0;
tr210:
#line 88 "include/redis_protocol_parser.rl"
	{_command = command::mget;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st162;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
#line 3956 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr212;
		case 101: goto tr212;
	}
	goto st0;
tr212:
#line 88 "include/redis_protocol_parser.rl"
	{_command = command::mget;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st163;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
#line 3972 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr213;
		case 116: goto tr213;
	}
	goto st0;
tr211:
#line 86 "include/redis_protocol_parser.rl"
	{_command = command::mset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st164;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
#line 3988 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr214;
		case 101: goto tr214;
	}
	goto st0;
tr214:
#line 86 "include/redis_protocol_parser.rl"
	{_command = command::mset;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st165;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
#line 4004 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr215;
		case 116: goto tr215;
	}
	goto st0;
tr22:
#line 91 "include/redis_protocol_parser.rl"
	{_command = command::ping;}
#line 142 "include/redis_protocol_parser.rl"
	{_command = command::pexpire; }
#line 145 "include/redis_protocol_parser.rl"
	{_command = command::persist; }
#line 144 "include/redis_protocol_parser.rl"
	{_command = command::pttl; }
#line 183 "include/redis_protocol_parser.rl"
	{_command = command::pfadd; }
#line 184 "include/redis_protocol_parser.rl"
	{_command = command::pfcount; }
#line 185 "include/redis_protocol_parser.rl"
	{_command = command::pfmerge; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st166;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
#line 4032 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr216;
		case 70: goto tr217;
		case 73: goto tr218;
		case 84: goto tr219;
		case 101: goto tr216;
		case 102: goto tr217;
		case 105: goto tr218;
		case 116: goto tr219;
	}
	goto st0;
tr216:
#line 142 "include/redis_protocol_parser.rl"
	{_command = command::pexpire; }
#line 145 "include/redis_protocol_parser.rl"
	{_command = command::persist; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st167;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
#line 4056 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr220;
		case 88: goto tr221;
		case 114: goto tr220;
		case 120: goto tr221;
	}
	goto st0;
tr220:
#line 145 "include/redis_protocol_parser.rl"
	{_command = command::persist; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st168;
st168:
	if ( ++p == pe )
		goto _test_eof168;
case 168:
#line 4074 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr222;
		case 115: goto tr222;
	}
	goto st0;
tr222:
#line 145 "include/redis_protocol_parser.rl"
	{_command = command::persist; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st169;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
#line 4090 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr223;
		case 105: goto tr223;
	}
	goto st0;
tr223:
#line 145 "include/redis_protocol_parser.rl"
	{_command = command::persist; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st170;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
#line 4106 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr224;
		case 115: goto tr224;
	}
	goto st0;
tr224:
#line 145 "include/redis_protocol_parser.rl"
	{_command = command::persist; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st171;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
#line 4122 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr225;
		case 116: goto tr225;
	}
	goto st0;
tr221:
#line 142 "include/redis_protocol_parser.rl"
	{_command = command::pexpire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st172;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
#line 4138 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 80: goto tr226;
		case 112: goto tr226;
	}
	goto st0;
tr226:
#line 142 "include/redis_protocol_parser.rl"
	{_command = command::pexpire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st173;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
#line 4154 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr227;
		case 105: goto tr227;
	}
	goto st0;
tr227:
#line 142 "include/redis_protocol_parser.rl"
	{_command = command::pexpire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st174;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
#line 4170 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr228;
		case 114: goto tr228;
	}
	goto st0;
tr228:
#line 142 "include/redis_protocol_parser.rl"
	{_command = command::pexpire; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st175;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
#line 4186 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr229;
		case 101: goto tr229;
	}
	goto st0;
tr217:
#line 183 "include/redis_protocol_parser.rl"
	{_command = command::pfadd; }
#line 184 "include/redis_protocol_parser.rl"
	{_command = command::pfcount; }
#line 185 "include/redis_protocol_parser.rl"
	{_command = command::pfmerge; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st176;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
#line 4206 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr230;
		case 67: goto tr231;
		case 77: goto tr232;
		case 97: goto tr230;
		case 99: goto tr231;
		case 109: goto tr232;
	}
	goto st0;
tr230:
#line 183 "include/redis_protocol_parser.rl"
	{_command = command::pfadd; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st177;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
#line 4226 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr233;
		case 100: goto tr233;
	}
	goto st0;
tr233:
#line 183 "include/redis_protocol_parser.rl"
	{_command = command::pfadd; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st178;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
#line 4242 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr234;
		case 100: goto tr234;
	}
	goto st0;
tr231:
#line 184 "include/redis_protocol_parser.rl"
	{_command = command::pfcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st179;
st179:
	if ( ++p == pe )
		goto _test_eof179;
case 179:
#line 4258 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr235;
		case 111: goto tr235;
	}
	goto st0;
tr235:
#line 184 "include/redis_protocol_parser.rl"
	{_command = command::pfcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st180;
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
#line 4274 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 85: goto tr236;
		case 117: goto tr236;
	}
	goto st0;
tr236:
#line 184 "include/redis_protocol_parser.rl"
	{_command = command::pfcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st181;
st181:
	if ( ++p == pe )
		goto _test_eof181;
case 181:
#line 4290 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr237;
		case 110: goto tr237;
	}
	goto st0;
tr237:
#line 184 "include/redis_protocol_parser.rl"
	{_command = command::pfcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st182;
st182:
	if ( ++p == pe )
		goto _test_eof182;
case 182:
#line 4306 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr238;
		case 116: goto tr238;
	}
	goto st0;
tr232:
#line 185 "include/redis_protocol_parser.rl"
	{_command = command::pfmerge; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st183;
st183:
	if ( ++p == pe )
		goto _test_eof183;
case 183:
#line 4322 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr239;
		case 101: goto tr239;
	}
	goto st0;
tr239:
#line 185 "include/redis_protocol_parser.rl"
	{_command = command::pfmerge; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st184;
st184:
	if ( ++p == pe )
		goto _test_eof184;
case 184:
#line 4338 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr240;
		case 114: goto tr240;
	}
	goto st0;
tr240:
#line 185 "include/redis_protocol_parser.rl"
	{_command = command::pfmerge; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st185;
st185:
	if ( ++p == pe )
		goto _test_eof185;
case 185:
#line 4354 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 71: goto tr241;
		case 103: goto tr241;
	}
	goto st0;
tr241:
#line 185 "include/redis_protocol_parser.rl"
	{_command = command::pfmerge; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st186;
st186:
	if ( ++p == pe )
		goto _test_eof186;
case 186:
#line 4370 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr242;
		case 101: goto tr242;
	}
	goto st0;
tr218:
#line 91 "include/redis_protocol_parser.rl"
	{_command = command::ping;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st187;
st187:
	if ( ++p == pe )
		goto _test_eof187;
case 187:
#line 4386 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr243;
		case 110: goto tr243;
	}
	goto st0;
tr243:
#line 91 "include/redis_protocol_parser.rl"
	{_command = command::ping;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st188;
st188:
	if ( ++p == pe )
		goto _test_eof188;
case 188:
#line 4402 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 71: goto tr244;
		case 103: goto tr244;
	}
	goto st0;
tr219:
#line 144 "include/redis_protocol_parser.rl"
	{_command = command::pttl; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st189;
st189:
	if ( ++p == pe )
		goto _test_eof189;
case 189:
#line 4418 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr245;
		case 116: goto tr245;
	}
	goto st0;
tr245:
#line 144 "include/redis_protocol_parser.rl"
	{_command = command::pttl; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st190;
st190:
	if ( ++p == pe )
		goto _test_eof190;
case 190:
#line 4434 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr246;
		case 108: goto tr246;
	}
	goto st0;
tr23:
#line 82 "include/redis_protocol_parser.rl"
	{_command = command::quit;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st191;
st191:
	if ( ++p == pe )
		goto _test_eof191;
case 191:
#line 4450 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 85: goto tr247;
		case 117: goto tr247;
	}
	goto st0;
tr247:
#line 82 "include/redis_protocol_parser.rl"
	{_command = command::quit;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st192;
st192:
	if ( ++p == pe )
		goto _test_eof192;
case 192:
#line 4466 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr248;
		case 105: goto tr248;
	}
	goto st0;
tr248:
#line 82 "include/redis_protocol_parser.rl"
	{_command = command::quit;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st193;
st193:
	if ( ++p == pe )
		goto _test_eof193;
case 193:
#line 4482 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr249;
		case 116: goto tr249;
	}
	goto st0;
tr24:
#line 109 "include/redis_protocol_parser.rl"
	{_command = command::rpushx;}
#line 108 "include/redis_protocol_parser.rl"
	{_command = command::rpush;}
#line 110 "include/redis_protocol_parser.rl"
	{_command = command::rpop;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st194;
st194:
	if ( ++p == pe )
		goto _test_eof194;
case 194:
#line 4502 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 80: goto tr250;
		case 112: goto tr250;
	}
	goto st0;
tr250:
#line 109 "include/redis_protocol_parser.rl"
	{_command = command::rpushx;}
#line 108 "include/redis_protocol_parser.rl"
	{_command = command::rpush;}
#line 110 "include/redis_protocol_parser.rl"
	{_command = command::rpop;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st195;
st195:
	if ( ++p == pe )
		goto _test_eof195;
case 195:
#line 4522 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr251;
		case 85: goto tr252;
		case 111: goto tr251;
		case 117: goto tr252;
	}
	goto st0;
tr251:
#line 110 "include/redis_protocol_parser.rl"
	{_command = command::rpop;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st196;
st196:
	if ( ++p == pe )
		goto _test_eof196;
case 196:
#line 4540 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 80: goto tr253;
		case 112: goto tr253;
	}
	goto st0;
tr252:
#line 109 "include/redis_protocol_parser.rl"
	{_command = command::rpushx;}
#line 108 "include/redis_protocol_parser.rl"
	{_command = command::rpush;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st197;
st197:
	if ( ++p == pe )
		goto _test_eof197;
case 197:
#line 4558 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr254;
		case 115: goto tr254;
	}
	goto st0;
tr254:
#line 109 "include/redis_protocol_parser.rl"
	{_command = command::rpushx;}
#line 108 "include/redis_protocol_parser.rl"
	{_command = command::rpush;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st198;
st198:
	if ( ++p == pe )
		goto _test_eof198;
case 198:
#line 4576 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 72: goto tr255;
		case 104: goto tr255;
	}
	goto st0;
tr255:
#line 109 "include/redis_protocol_parser.rl"
	{_command = command::rpushx;}
#line 108 "include/redis_protocol_parser.rl"
	{_command = command::rpush;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st199;
st199:
	if ( ++p == pe )
		goto _test_eof199;
case 199:
#line 4594 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 88: goto tr256;
		case 120: goto tr256;
	}
	goto st0;
tr25:
#line 177 "include/redis_protocol_parser.rl"
	{_command = command::setbit; }
#line 85 "include/redis_protocol_parser.rl"
	{_command = command::set;}
#line 99 "include/redis_protocol_parser.rl"
	{_command = command::strlen;}
#line 126 "include/redis_protocol_parser.rl"
	{_command = command::sadd;}
#line 127 "include/redis_protocol_parser.rl"
	{_command = command::scard;}
#line 128 "include/redis_protocol_parser.rl"
	{_command = command::sismember;}
#line 129 "include/redis_protocol_parser.rl"
	{_command = command::smembers;}
#line 131 "include/redis_protocol_parser.rl"
	{_command = command::srem;}
#line 133 "include/redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
#line 132 "include/redis_protocol_parser.rl"
	{_command = command::sdiff;}
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 134 "include/redis_protocol_parser.rl"
	{_command = command::sinter;}
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 136 "include/redis_protocol_parser.rl"
	{_command = command::sunion;}
#line 138 "include/redis_protocol_parser.rl"
	{_command = command::smove;}
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 139 "include/redis_protocol_parser.rl"
	{_command = command::spop;}
#line 170 "include/redis_protocol_parser.rl"
	{_command = command::select; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st200;
st200:
	if ( ++p == pe )
		goto _test_eof200;
case 200:
#line 4645 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr257;
		case 67: goto tr258;
		case 68: goto tr259;
		case 69: goto tr260;
		case 73: goto tr261;
		case 77: goto tr262;
		case 80: goto tr263;
		case 82: goto tr264;
		case 84: goto tr265;
		case 85: goto tr266;
		case 97: goto tr257;
		case 99: goto tr258;
		case 100: goto tr259;
		case 101: goto tr260;
		case 105: goto tr261;
		case 109: goto tr262;
		case 112: goto tr263;
		case 114: goto tr264;
		case 116: goto tr265;
		case 117: goto tr266;
	}
	goto st0;
tr257:
#line 126 "include/redis_protocol_parser.rl"
	{_command = command::sadd;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st201;
st201:
	if ( ++p == pe )
		goto _test_eof201;
case 201:
#line 4679 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr267;
		case 100: goto tr267;
	}
	goto st0;
tr267:
#line 126 "include/redis_protocol_parser.rl"
	{_command = command::sadd;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st202;
st202:
	if ( ++p == pe )
		goto _test_eof202;
case 202:
#line 4695 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr268;
		case 100: goto tr268;
	}
	goto st0;
tr258:
#line 127 "include/redis_protocol_parser.rl"
	{_command = command::scard;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st203;
st203:
	if ( ++p == pe )
		goto _test_eof203;
case 203:
#line 4711 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr269;
		case 97: goto tr269;
	}
	goto st0;
tr269:
#line 127 "include/redis_protocol_parser.rl"
	{_command = command::scard;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st204;
st204:
	if ( ++p == pe )
		goto _test_eof204;
case 204:
#line 4727 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr270;
		case 114: goto tr270;
	}
	goto st0;
tr270:
#line 127 "include/redis_protocol_parser.rl"
	{_command = command::scard;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st205;
st205:
	if ( ++p == pe )
		goto _test_eof205;
case 205:
#line 4743 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr271;
		case 100: goto tr271;
	}
	goto st0;
tr259:
#line 133 "include/redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
#line 132 "include/redis_protocol_parser.rl"
	{_command = command::sdiff;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st206;
st206:
	if ( ++p == pe )
		goto _test_eof206;
case 206:
#line 4761 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr272;
		case 105: goto tr272;
	}
	goto st0;
tr272:
#line 133 "include/redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
#line 132 "include/redis_protocol_parser.rl"
	{_command = command::sdiff;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st207;
st207:
	if ( ++p == pe )
		goto _test_eof207;
case 207:
#line 4779 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 70: goto tr273;
		case 102: goto tr273;
	}
	goto st0;
tr273:
#line 133 "include/redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
#line 132 "include/redis_protocol_parser.rl"
	{_command = command::sdiff;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st208;
st208:
	if ( ++p == pe )
		goto _test_eof208;
case 208:
#line 4797 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 70: goto tr274;
		case 102: goto tr274;
	}
	goto st0;
tr274:
#line 133 "include/redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
#line 132 "include/redis_protocol_parser.rl"
	{_command = command::sdiff;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st209;
st209:
	if ( ++p == pe )
		goto _test_eof209;
case 209:
#line 4815 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 83: goto tr275;
		case 115: goto tr275;
	}
	goto st0;
tr275:
#line 133 "include/redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st210;
st210:
	if ( ++p == pe )
		goto _test_eof210;
case 210:
#line 4832 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr276;
		case 116: goto tr276;
	}
	goto st0;
tr276:
#line 133 "include/redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st211;
st211:
	if ( ++p == pe )
		goto _test_eof211;
case 211:
#line 4848 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr277;
		case 111: goto tr277;
	}
	goto st0;
tr277:
#line 133 "include/redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st212;
st212:
	if ( ++p == pe )
		goto _test_eof212;
case 212:
#line 4864 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr278;
		case 114: goto tr278;
	}
	goto st0;
tr278:
#line 133 "include/redis_protocol_parser.rl"
	{_command = command::sdiffstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st213;
st213:
	if ( ++p == pe )
		goto _test_eof213;
case 213:
#line 4880 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr279;
		case 101: goto tr279;
	}
	goto st0;
tr260:
#line 177 "include/redis_protocol_parser.rl"
	{_command = command::setbit; }
#line 85 "include/redis_protocol_parser.rl"
	{_command = command::set;}
#line 170 "include/redis_protocol_parser.rl"
	{_command = command::select; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st214;
st214:
	if ( ++p == pe )
		goto _test_eof214;
case 214:
#line 4900 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr280;
		case 84: goto tr281;
		case 108: goto tr280;
		case 116: goto tr281;
	}
	goto st0;
tr280:
#line 170 "include/redis_protocol_parser.rl"
	{_command = command::select; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st215;
st215:
	if ( ++p == pe )
		goto _test_eof215;
case 215:
#line 4918 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr282;
		case 101: goto tr282;
	}
	goto st0;
tr282:
#line 170 "include/redis_protocol_parser.rl"
	{_command = command::select; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st216;
st216:
	if ( ++p == pe )
		goto _test_eof216;
case 216:
#line 4934 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr283;
		case 99: goto tr283;
	}
	goto st0;
tr283:
#line 170 "include/redis_protocol_parser.rl"
	{_command = command::select; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st217;
st217:
	if ( ++p == pe )
		goto _test_eof217;
case 217:
#line 4950 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr284;
		case 116: goto tr284;
	}
	goto st0;
tr281:
#line 177 "include/redis_protocol_parser.rl"
	{_command = command::setbit; }
#line 85 "include/redis_protocol_parser.rl"
	{_command = command::set;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st218;
st218:
	if ( ++p == pe )
		goto _test_eof218;
case 218:
#line 4968 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 66: goto tr285;
		case 98: goto tr285;
	}
	goto st0;
tr285:
#line 177 "include/redis_protocol_parser.rl"
	{_command = command::setbit; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st219;
st219:
	if ( ++p == pe )
		goto _test_eof219;
case 219:
#line 4985 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr286;
		case 105: goto tr286;
	}
	goto st0;
tr286:
#line 177 "include/redis_protocol_parser.rl"
	{_command = command::setbit; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st220;
st220:
	if ( ++p == pe )
		goto _test_eof220;
case 220:
#line 5001 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr287;
		case 116: goto tr287;
	}
	goto st0;
tr261:
#line 128 "include/redis_protocol_parser.rl"
	{_command = command::sismember;}
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 134 "include/redis_protocol_parser.rl"
	{_command = command::sinter;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st221;
st221:
	if ( ++p == pe )
		goto _test_eof221;
case 221:
#line 5021 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr288;
		case 83: goto tr289;
		case 110: goto tr288;
		case 115: goto tr289;
	}
	goto st0;
tr288:
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 134 "include/redis_protocol_parser.rl"
	{_command = command::sinter;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st222;
st222:
	if ( ++p == pe )
		goto _test_eof222;
case 222:
#line 5041 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr290;
		case 116: goto tr290;
	}
	goto st0;
tr290:
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 134 "include/redis_protocol_parser.rl"
	{_command = command::sinter;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st223;
st223:
	if ( ++p == pe )
		goto _test_eof223;
case 223:
#line 5059 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr291;
		case 101: goto tr291;
	}
	goto st0;
tr291:
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 134 "include/redis_protocol_parser.rl"
	{_command = command::sinter;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st224;
st224:
	if ( ++p == pe )
		goto _test_eof224;
case 224:
#line 5077 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr292;
		case 114: goto tr292;
	}
	goto st0;
tr292:
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 134 "include/redis_protocol_parser.rl"
	{_command = command::sinter;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st225;
st225:
	if ( ++p == pe )
		goto _test_eof225;
case 225:
#line 5095 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 83: goto tr293;
		case 115: goto tr293;
	}
	goto st0;
tr293:
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st226;
st226:
	if ( ++p == pe )
		goto _test_eof226;
case 226:
#line 5112 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr294;
		case 116: goto tr294;
	}
	goto st0;
tr294:
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st227;
st227:
	if ( ++p == pe )
		goto _test_eof227;
case 227:
#line 5128 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr295;
		case 111: goto tr295;
	}
	goto st0;
tr295:
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st228;
st228:
	if ( ++p == pe )
		goto _test_eof228;
case 228:
#line 5144 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr296;
		case 114: goto tr296;
	}
	goto st0;
tr296:
#line 135 "include/redis_protocol_parser.rl"
	{_command = command::sinterstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st229;
st229:
	if ( ++p == pe )
		goto _test_eof229;
case 229:
#line 5160 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr297;
		case 101: goto tr297;
	}
	goto st0;
tr289:
#line 128 "include/redis_protocol_parser.rl"
	{_command = command::sismember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st230;
st230:
	if ( ++p == pe )
		goto _test_eof230;
case 230:
#line 5176 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr298;
		case 109: goto tr298;
	}
	goto st0;
tr298:
#line 128 "include/redis_protocol_parser.rl"
	{_command = command::sismember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st231;
st231:
	if ( ++p == pe )
		goto _test_eof231;
case 231:
#line 5192 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr299;
		case 101: goto tr299;
	}
	goto st0;
tr299:
#line 128 "include/redis_protocol_parser.rl"
	{_command = command::sismember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st232;
st232:
	if ( ++p == pe )
		goto _test_eof232;
case 232:
#line 5208 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr300;
		case 109: goto tr300;
	}
	goto st0;
tr300:
#line 128 "include/redis_protocol_parser.rl"
	{_command = command::sismember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st233;
st233:
	if ( ++p == pe )
		goto _test_eof233;
case 233:
#line 5224 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 66: goto tr301;
		case 98: goto tr301;
	}
	goto st0;
tr301:
#line 128 "include/redis_protocol_parser.rl"
	{_command = command::sismember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st234;
st234:
	if ( ++p == pe )
		goto _test_eof234;
case 234:
#line 5240 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr302;
		case 101: goto tr302;
	}
	goto st0;
tr302:
#line 128 "include/redis_protocol_parser.rl"
	{_command = command::sismember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st235;
st235:
	if ( ++p == pe )
		goto _test_eof235;
case 235:
#line 5256 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr303;
		case 114: goto tr303;
	}
	goto st0;
tr262:
#line 129 "include/redis_protocol_parser.rl"
	{_command = command::smembers;}
#line 138 "include/redis_protocol_parser.rl"
	{_command = command::smove;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st236;
st236:
	if ( ++p == pe )
		goto _test_eof236;
case 236:
#line 5274 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr304;
		case 79: goto tr305;
		case 101: goto tr304;
		case 111: goto tr305;
	}
	goto st0;
tr304:
#line 129 "include/redis_protocol_parser.rl"
	{_command = command::smembers;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st237;
st237:
	if ( ++p == pe )
		goto _test_eof237;
case 237:
#line 5292 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr306;
		case 109: goto tr306;
	}
	goto st0;
tr306:
#line 129 "include/redis_protocol_parser.rl"
	{_command = command::smembers;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st238;
st238:
	if ( ++p == pe )
		goto _test_eof238;
case 238:
#line 5308 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 66: goto tr307;
		case 98: goto tr307;
	}
	goto st0;
tr307:
#line 129 "include/redis_protocol_parser.rl"
	{_command = command::smembers;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st239;
st239:
	if ( ++p == pe )
		goto _test_eof239;
case 239:
#line 5324 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr308;
		case 101: goto tr308;
	}
	goto st0;
tr308:
#line 129 "include/redis_protocol_parser.rl"
	{_command = command::smembers;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st240;
st240:
	if ( ++p == pe )
		goto _test_eof240;
case 240:
#line 5340 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr309;
		case 114: goto tr309;
	}
	goto st0;
tr309:
#line 129 "include/redis_protocol_parser.rl"
	{_command = command::smembers;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st241;
st241:
	if ( ++p == pe )
		goto _test_eof241;
case 241:
#line 5356 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr310;
		case 115: goto tr310;
	}
	goto st0;
tr305:
#line 138 "include/redis_protocol_parser.rl"
	{_command = command::smove;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st242;
st242:
	if ( ++p == pe )
		goto _test_eof242;
case 242:
#line 5372 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 86: goto tr311;
		case 118: goto tr311;
	}
	goto st0;
tr311:
#line 138 "include/redis_protocol_parser.rl"
	{_command = command::smove;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st243;
st243:
	if ( ++p == pe )
		goto _test_eof243;
case 243:
#line 5388 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr312;
		case 101: goto tr312;
	}
	goto st0;
tr263:
#line 139 "include/redis_protocol_parser.rl"
	{_command = command::spop;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st244;
st244:
	if ( ++p == pe )
		goto _test_eof244;
case 244:
#line 5404 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr313;
		case 111: goto tr313;
	}
	goto st0;
tr313:
#line 139 "include/redis_protocol_parser.rl"
	{_command = command::spop;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st245;
st245:
	if ( ++p == pe )
		goto _test_eof245;
case 245:
#line 5420 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 80: goto tr314;
		case 112: goto tr314;
	}
	goto st0;
tr264:
#line 131 "include/redis_protocol_parser.rl"
	{_command = command::srem;}
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st246;
st246:
	if ( ++p == pe )
		goto _test_eof246;
case 246:
#line 5438 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr315;
		case 69: goto tr316;
		case 97: goto tr315;
		case 101: goto tr316;
	}
	goto st0;
tr315:
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st247;
st247:
	if ( ++p == pe )
		goto _test_eof247;
case 247:
#line 5456 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr317;
		case 110: goto tr317;
	}
	goto st0;
tr317:
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st248;
st248:
	if ( ++p == pe )
		goto _test_eof248;
case 248:
#line 5472 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr318;
		case 100: goto tr318;
	}
	goto st0;
tr318:
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st249;
st249:
	if ( ++p == pe )
		goto _test_eof249;
case 249:
#line 5488 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr319;
		case 109: goto tr319;
	}
	goto st0;
tr319:
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st250;
st250:
	if ( ++p == pe )
		goto _test_eof250;
case 250:
#line 5504 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr320;
		case 101: goto tr320;
	}
	goto st0;
tr320:
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st251;
st251:
	if ( ++p == pe )
		goto _test_eof251;
case 251:
#line 5520 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr321;
		case 109: goto tr321;
	}
	goto st0;
tr321:
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st252;
st252:
	if ( ++p == pe )
		goto _test_eof252;
case 252:
#line 5536 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 66: goto tr322;
		case 98: goto tr322;
	}
	goto st0;
tr322:
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st253;
st253:
	if ( ++p == pe )
		goto _test_eof253;
case 253:
#line 5552 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr323;
		case 101: goto tr323;
	}
	goto st0;
tr323:
#line 130 "include/redis_protocol_parser.rl"
	{_command = command::srandmember;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st254;
st254:
	if ( ++p == pe )
		goto _test_eof254;
case 254:
#line 5568 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr324;
		case 114: goto tr324;
	}
	goto st0;
tr316:
#line 131 "include/redis_protocol_parser.rl"
	{_command = command::srem;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st255;
st255:
	if ( ++p == pe )
		goto _test_eof255;
case 255:
#line 5584 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr325;
		case 109: goto tr325;
	}
	goto st0;
tr265:
#line 99 "include/redis_protocol_parser.rl"
	{_command = command::strlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st256;
st256:
	if ( ++p == pe )
		goto _test_eof256;
case 256:
#line 5600 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr326;
		case 114: goto tr326;
	}
	goto st0;
tr326:
#line 99 "include/redis_protocol_parser.rl"
	{_command = command::strlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st257;
st257:
	if ( ++p == pe )
		goto _test_eof257;
case 257:
#line 5616 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr327;
		case 108: goto tr327;
	}
	goto st0;
tr327:
#line 99 "include/redis_protocol_parser.rl"
	{_command = command::strlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st258;
st258:
	if ( ++p == pe )
		goto _test_eof258;
case 258:
#line 5632 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr328;
		case 101: goto tr328;
	}
	goto st0;
tr328:
#line 99 "include/redis_protocol_parser.rl"
	{_command = command::strlen;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st259;
st259:
	if ( ++p == pe )
		goto _test_eof259;
case 259:
#line 5648 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr329;
		case 110: goto tr329;
	}
	goto st0;
tr266:
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 136 "include/redis_protocol_parser.rl"
	{_command = command::sunion;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st260;
st260:
	if ( ++p == pe )
		goto _test_eof260;
case 260:
#line 5666 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr330;
		case 110: goto tr330;
	}
	goto st0;
tr330:
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 136 "include/redis_protocol_parser.rl"
	{_command = command::sunion;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st261;
st261:
	if ( ++p == pe )
		goto _test_eof261;
case 261:
#line 5684 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr331;
		case 105: goto tr331;
	}
	goto st0;
tr331:
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 136 "include/redis_protocol_parser.rl"
	{_command = command::sunion;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st262;
st262:
	if ( ++p == pe )
		goto _test_eof262;
case 262:
#line 5702 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr332;
		case 111: goto tr332;
	}
	goto st0;
tr332:
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 136 "include/redis_protocol_parser.rl"
	{_command = command::sunion;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st263;
st263:
	if ( ++p == pe )
		goto _test_eof263;
case 263:
#line 5720 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr333;
		case 110: goto tr333;
	}
	goto st0;
tr333:
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 136 "include/redis_protocol_parser.rl"
	{_command = command::sunion;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st264;
st264:
	if ( ++p == pe )
		goto _test_eof264;
case 264:
#line 5738 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 83: goto tr334;
		case 115: goto tr334;
	}
	goto st0;
tr334:
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st265;
st265:
	if ( ++p == pe )
		goto _test_eof265;
case 265:
#line 5755 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr335;
		case 116: goto tr335;
	}
	goto st0;
tr335:
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st266;
st266:
	if ( ++p == pe )
		goto _test_eof266;
case 266:
#line 5771 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr336;
		case 111: goto tr336;
	}
	goto st0;
tr336:
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st267;
st267:
	if ( ++p == pe )
		goto _test_eof267;
case 267:
#line 5787 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr337;
		case 114: goto tr337;
	}
	goto st0;
tr337:
#line 137 "include/redis_protocol_parser.rl"
	{_command = command::sunionstore;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st268;
st268:
	if ( ++p == pe )
		goto _test_eof268;
case 268:
#line 5803 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr338;
		case 101: goto tr338;
	}
	goto st0;
tr26:
#line 140 "include/redis_protocol_parser.rl"
	{_command = command::type; }
#line 143 "include/redis_protocol_parser.rl"
	{_command = command::ttl; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st269;
st269:
	if ( ++p == pe )
		goto _test_eof269;
case 269:
#line 5821 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr339;
		case 89: goto tr340;
		case 116: goto tr339;
		case 121: goto tr340;
	}
	goto st0;
tr339:
#line 143 "include/redis_protocol_parser.rl"
	{_command = command::ttl; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st270;
st270:
	if ( ++p == pe )
		goto _test_eof270;
case 270:
#line 5839 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr341;
		case 108: goto tr341;
	}
	goto st0;
tr340:
#line 140 "include/redis_protocol_parser.rl"
	{_command = command::type; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st271;
st271:
	if ( ++p == pe )
		goto _test_eof271;
case 271:
#line 5855 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 80: goto tr342;
		case 112: goto tr342;
	}
	goto st0;
tr342:
#line 140 "include/redis_protocol_parser.rl"
	{_command = command::type; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st272;
st272:
	if ( ++p == pe )
		goto _test_eof272;
case 272:
#line 5871 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr343;
		case 101: goto tr343;
	}
	goto st0;
tr27:
#line 146 "include/redis_protocol_parser.rl"
	{_command = command::zadd; }
#line 147 "include/redis_protocol_parser.rl"
	{_command = command::zcard; }
#line 148 "include/redis_protocol_parser.rl"
	{_command = command::zcount; }
#line 149 "include/redis_protocol_parser.rl"
	{_command = command::zincrby; }
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 151 "include/redis_protocol_parser.rl"
	{_command = command::zrank; }
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 152 "include/redis_protocol_parser.rl"
	{_command = command::zrem; }
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 155 "include/redis_protocol_parser.rl"
	{_command = command::zrevrange; }
#line 157 "include/redis_protocol_parser.rl"
	{_command = command::zrevrank; }
#line 158 "include/redis_protocol_parser.rl"
	{_command = command::zscore; }
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 161 "include/redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
#line 162 "include/redis_protocol_parser.rl"
	{_command = command::zunion; }
#line 163 "include/redis_protocol_parser.rl"
	{_command = command::zinter; }
#line 164 "include/redis_protocol_parser.rl"
	{_command = command::zdiff; }
#line 165 "include/redis_protocol_parser.rl"
	{_command = command::zscan; }
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 168 "include/redis_protocol_parser.rl"
	{_command = command::zlexcount;}
#line 150 "include/redis_protocol_parser.rl"
	{_command = command::zrange;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st273;
st273:
	if ( ++p == pe )
		goto _test_eof273;
case 273:
#line 5933 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr344;
		case 67: goto tr345;
		case 68: goto tr346;
		case 73: goto tr347;
		case 76: goto tr348;
		case 82: goto tr349;
		case 83: goto tr350;
		case 85: goto tr351;
		case 97: goto tr344;
		case 99: goto tr345;
		case 100: goto tr346;
		case 105: goto tr347;
		case 108: goto tr348;
		case 114: goto tr349;
		case 115: goto tr350;
		case 117: goto tr351;
	}
	goto st0;
tr344:
#line 146 "include/redis_protocol_parser.rl"
	{_command = command::zadd; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st274;
st274:
	if ( ++p == pe )
		goto _test_eof274;
case 274:
#line 5963 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr352;
		case 100: goto tr352;
	}
	goto st0;
tr352:
#line 146 "include/redis_protocol_parser.rl"
	{_command = command::zadd; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st275;
st275:
	if ( ++p == pe )
		goto _test_eof275;
case 275:
#line 5979 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr353;
		case 100: goto tr353;
	}
	goto st0;
tr345:
#line 147 "include/redis_protocol_parser.rl"
	{_command = command::zcard; }
#line 148 "include/redis_protocol_parser.rl"
	{_command = command::zcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st276;
st276:
	if ( ++p == pe )
		goto _test_eof276;
case 276:
#line 5997 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr354;
		case 79: goto tr355;
		case 97: goto tr354;
		case 111: goto tr355;
	}
	goto st0;
tr354:
#line 147 "include/redis_protocol_parser.rl"
	{_command = command::zcard; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st277;
st277:
	if ( ++p == pe )
		goto _test_eof277;
case 277:
#line 6015 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr356;
		case 114: goto tr356;
	}
	goto st0;
tr356:
#line 147 "include/redis_protocol_parser.rl"
	{_command = command::zcard; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st278;
st278:
	if ( ++p == pe )
		goto _test_eof278;
case 278:
#line 6031 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 68: goto tr357;
		case 100: goto tr357;
	}
	goto st0;
tr355:
#line 148 "include/redis_protocol_parser.rl"
	{_command = command::zcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st279;
st279:
	if ( ++p == pe )
		goto _test_eof279;
case 279:
#line 6047 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 85: goto tr358;
		case 117: goto tr358;
	}
	goto st0;
tr358:
#line 148 "include/redis_protocol_parser.rl"
	{_command = command::zcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st280;
st280:
	if ( ++p == pe )
		goto _test_eof280;
case 280:
#line 6063 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr359;
		case 110: goto tr359;
	}
	goto st0;
tr359:
#line 148 "include/redis_protocol_parser.rl"
	{_command = command::zcount; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st281;
st281:
	if ( ++p == pe )
		goto _test_eof281;
case 281:
#line 6079 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr360;
		case 116: goto tr360;
	}
	goto st0;
tr346:
#line 161 "include/redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st282;
st282:
	if ( ++p == pe )
		goto _test_eof282;
case 282:
#line 6095 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr361;
		case 105: goto tr361;
	}
	goto st0;
tr361:
#line 161 "include/redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st283;
st283:
	if ( ++p == pe )
		goto _test_eof283;
case 283:
#line 6111 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 70: goto tr362;
		case 102: goto tr362;
	}
	goto st0;
tr362:
#line 161 "include/redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st284;
st284:
	if ( ++p == pe )
		goto _test_eof284;
case 284:
#line 6127 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 70: goto tr363;
		case 102: goto tr363;
	}
	goto st0;
tr363:
#line 161 "include/redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st285;
st285:
	if ( ++p == pe )
		goto _test_eof285;
case 285:
#line 6143 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr364;
		case 115: goto tr364;
	}
	goto st0;
tr364:
#line 161 "include/redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st286;
st286:
	if ( ++p == pe )
		goto _test_eof286;
case 286:
#line 6159 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr365;
		case 116: goto tr365;
	}
	goto st0;
tr365:
#line 161 "include/redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st287;
st287:
	if ( ++p == pe )
		goto _test_eof287;
case 287:
#line 6175 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr366;
		case 111: goto tr366;
	}
	goto st0;
tr366:
#line 161 "include/redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st288;
st288:
	if ( ++p == pe )
		goto _test_eof288;
case 288:
#line 6191 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr367;
		case 114: goto tr367;
	}
	goto st0;
tr367:
#line 161 "include/redis_protocol_parser.rl"
	{_command = command::zdiffstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st289;
st289:
	if ( ++p == pe )
		goto _test_eof289;
case 289:
#line 6207 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr368;
		case 101: goto tr368;
	}
	goto st0;
tr347:
#line 149 "include/redis_protocol_parser.rl"
	{_command = command::zincrby; }
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 163 "include/redis_protocol_parser.rl"
	{_command = command::zinter; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st290;
st290:
	if ( ++p == pe )
		goto _test_eof290;
case 290:
#line 6227 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr369;
		case 110: goto tr369;
	}
	goto st0;
tr369:
#line 149 "include/redis_protocol_parser.rl"
	{_command = command::zincrby; }
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 163 "include/redis_protocol_parser.rl"
	{_command = command::zinter; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st291;
st291:
	if ( ++p == pe )
		goto _test_eof291;
case 291:
#line 6247 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr370;
		case 84: goto tr371;
		case 99: goto tr370;
		case 116: goto tr371;
	}
	goto st0;
tr370:
#line 149 "include/redis_protocol_parser.rl"
	{_command = command::zincrby; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st292;
st292:
	if ( ++p == pe )
		goto _test_eof292;
case 292:
#line 6265 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr372;
		case 114: goto tr372;
	}
	goto st0;
tr372:
#line 149 "include/redis_protocol_parser.rl"
	{_command = command::zincrby; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st293;
st293:
	if ( ++p == pe )
		goto _test_eof293;
case 293:
#line 6281 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 66: goto tr373;
		case 98: goto tr373;
	}
	goto st0;
tr373:
#line 149 "include/redis_protocol_parser.rl"
	{_command = command::zincrby; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st294;
st294:
	if ( ++p == pe )
		goto _test_eof294;
case 294:
#line 6297 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 89: goto tr374;
		case 121: goto tr374;
	}
	goto st0;
tr371:
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 163 "include/redis_protocol_parser.rl"
	{_command = command::zinter; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st295;
st295:
	if ( ++p == pe )
		goto _test_eof295;
case 295:
#line 6315 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr375;
		case 101: goto tr375;
	}
	goto st0;
tr375:
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 163 "include/redis_protocol_parser.rl"
	{_command = command::zinter; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st296;
st296:
	if ( ++p == pe )
		goto _test_eof296;
case 296:
#line 6333 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr376;
		case 114: goto tr376;
	}
	goto st0;
tr376:
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 163 "include/redis_protocol_parser.rl"
	{_command = command::zinter; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st297;
st297:
	if ( ++p == pe )
		goto _test_eof297;
case 297:
#line 6351 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 83: goto tr377;
		case 115: goto tr377;
	}
	goto st0;
tr377:
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st298;
st298:
	if ( ++p == pe )
		goto _test_eof298;
case 298:
#line 6368 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr378;
		case 116: goto tr378;
	}
	goto st0;
tr378:
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st299;
st299:
	if ( ++p == pe )
		goto _test_eof299;
case 299:
#line 6384 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr379;
		case 111: goto tr379;
	}
	goto st0;
tr379:
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st300;
st300:
	if ( ++p == pe )
		goto _test_eof300;
case 300:
#line 6400 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr380;
		case 114: goto tr380;
	}
	goto st0;
tr380:
#line 160 "include/redis_protocol_parser.rl"
	{_command = command::zinterstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st301;
st301:
	if ( ++p == pe )
		goto _test_eof301;
case 301:
#line 6416 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr381;
		case 101: goto tr381;
	}
	goto st0;
tr348:
#line 168 "include/redis_protocol_parser.rl"
	{_command = command::zlexcount;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st302;
st302:
	if ( ++p == pe )
		goto _test_eof302;
case 302:
#line 6432 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr382;
		case 101: goto tr382;
	}
	goto st0;
tr382:
#line 168 "include/redis_protocol_parser.rl"
	{_command = command::zlexcount;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st303;
st303:
	if ( ++p == pe )
		goto _test_eof303;
case 303:
#line 6448 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 88: goto tr383;
		case 120: goto tr383;
	}
	goto st0;
tr383:
#line 168 "include/redis_protocol_parser.rl"
	{_command = command::zlexcount;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st304;
st304:
	if ( ++p == pe )
		goto _test_eof304;
case 304:
#line 6464 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr384;
		case 99: goto tr384;
	}
	goto st0;
tr384:
#line 168 "include/redis_protocol_parser.rl"
	{_command = command::zlexcount;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st305;
st305:
	if ( ++p == pe )
		goto _test_eof305;
case 305:
#line 6480 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr385;
		case 111: goto tr385;
	}
	goto st0;
tr385:
#line 168 "include/redis_protocol_parser.rl"
	{_command = command::zlexcount;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st306;
st306:
	if ( ++p == pe )
		goto _test_eof306;
case 306:
#line 6496 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 85: goto tr386;
		case 117: goto tr386;
	}
	goto st0;
tr386:
#line 168 "include/redis_protocol_parser.rl"
	{_command = command::zlexcount;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st307;
st307:
	if ( ++p == pe )
		goto _test_eof307;
case 307:
#line 6512 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr387;
		case 110: goto tr387;
	}
	goto st0;
tr387:
#line 168 "include/redis_protocol_parser.rl"
	{_command = command::zlexcount;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st308;
st308:
	if ( ++p == pe )
		goto _test_eof308;
case 308:
#line 6528 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr388;
		case 116: goto tr388;
	}
	goto st0;
tr349:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 151 "include/redis_protocol_parser.rl"
	{_command = command::zrank; }
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 152 "include/redis_protocol_parser.rl"
	{_command = command::zrem; }
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 155 "include/redis_protocol_parser.rl"
	{_command = command::zrevrange; }
#line 157 "include/redis_protocol_parser.rl"
	{_command = command::zrevrank; }
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 150 "include/redis_protocol_parser.rl"
	{_command = command::zrange;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st309;
st309:
	if ( ++p == pe )
		goto _test_eof309;
case 309:
#line 6564 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr389;
		case 69: goto tr390;
		case 97: goto tr389;
		case 101: goto tr390;
	}
	goto st0;
tr389:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 151 "include/redis_protocol_parser.rl"
	{_command = command::zrank; }
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 150 "include/redis_protocol_parser.rl"
	{_command = command::zrange;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st310;
st310:
	if ( ++p == pe )
		goto _test_eof310;
case 310:
#line 6588 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr391;
		case 110: goto tr391;
	}
	goto st0;
tr391:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 151 "include/redis_protocol_parser.rl"
	{_command = command::zrank; }
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 150 "include/redis_protocol_parser.rl"
	{_command = command::zrange;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st311;
st311:
	if ( ++p == pe )
		goto _test_eof311;
case 311:
#line 6610 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 71: goto tr392;
		case 75: goto tr393;
		case 103: goto tr392;
		case 107: goto tr393;
	}
	goto st0;
tr392:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 150 "include/redis_protocol_parser.rl"
	{_command = command::zrange;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st312;
st312:
	if ( ++p == pe )
		goto _test_eof312;
case 312:
#line 6632 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr394;
		case 101: goto tr394;
	}
	goto st0;
tr394:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 150 "include/redis_protocol_parser.rl"
	{_command = command::zrange;}
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st313;
st313:
	if ( ++p == pe )
		goto _test_eof313;
case 313:
#line 6652 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 66: goto tr395;
		case 98: goto tr395;
	}
	goto st0;
tr395:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st314;
st314:
	if ( ++p == pe )
		goto _test_eof314;
case 314:
#line 6671 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 89: goto tr396;
		case 121: goto tr396;
	}
	goto st0;
tr396:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st315;
st315:
	if ( ++p == pe )
		goto _test_eof315;
case 315:
#line 6689 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr397;
		case 83: goto tr398;
		case 108: goto tr397;
		case 115: goto tr398;
	}
	goto st0;
tr397:
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st316;
st316:
	if ( ++p == pe )
		goto _test_eof316;
case 316:
#line 6707 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr399;
		case 101: goto tr399;
	}
	goto st0;
tr399:
#line 166 "include/redis_protocol_parser.rl"
	{_command = command::zrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st317;
st317:
	if ( ++p == pe )
		goto _test_eof317;
case 317:
#line 6723 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 88: goto tr400;
		case 120: goto tr400;
	}
	goto st0;
tr398:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st318;
st318:
	if ( ++p == pe )
		goto _test_eof318;
case 318:
#line 6739 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr401;
		case 99: goto tr401;
	}
	goto st0;
tr401:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st319;
st319:
	if ( ++p == pe )
		goto _test_eof319;
case 319:
#line 6755 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr402;
		case 111: goto tr402;
	}
	goto st0;
tr402:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st320;
st320:
	if ( ++p == pe )
		goto _test_eof320;
case 320:
#line 6771 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr403;
		case 114: goto tr403;
	}
	goto st0;
tr403:
#line 167 "include/redis_protocol_parser.rl"
	{_command = command::zrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st321;
st321:
	if ( ++p == pe )
		goto _test_eof321;
case 321:
#line 6787 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr404;
		case 101: goto tr404;
	}
	goto st0;
tr390:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 152 "include/redis_protocol_parser.rl"
	{_command = command::zrem; }
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 155 "include/redis_protocol_parser.rl"
	{_command = command::zrevrange; }
#line 157 "include/redis_protocol_parser.rl"
	{_command = command::zrevrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st322;
st322:
	if ( ++p == pe )
		goto _test_eof322;
case 322:
#line 6815 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 77: goto tr405;
		case 86: goto tr406;
		case 109: goto tr405;
		case 118: goto tr406;
	}
	goto st0;
tr405:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 152 "include/redis_protocol_parser.rl"
	{_command = command::zrem; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st323;
st323:
	if ( ++p == pe )
		goto _test_eof323;
case 323:
#line 6839 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 82: goto tr407;
		case 114: goto tr407;
	}
	goto st0;
tr407:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st324;
st324:
	if ( ++p == pe )
		goto _test_eof324;
case 324:
#line 6860 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr408;
		case 97: goto tr408;
	}
	goto st0;
tr408:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st325;
st325:
	if ( ++p == pe )
		goto _test_eof325;
case 325:
#line 6880 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr409;
		case 110: goto tr409;
	}
	goto st0;
tr409:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st326;
st326:
	if ( ++p == pe )
		goto _test_eof326;
case 326:
#line 6900 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 71: goto tr410;
		case 103: goto tr410;
	}
	goto st0;
tr410:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st327;
st327:
	if ( ++p == pe )
		goto _test_eof327;
case 327:
#line 6920 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr411;
		case 101: goto tr411;
	}
	goto st0;
tr411:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st328;
st328:
	if ( ++p == pe )
		goto _test_eof328;
case 328:
#line 6940 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 66: goto tr412;
		case 98: goto tr412;
	}
	goto st0;
tr412:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st329;
st329:
	if ( ++p == pe )
		goto _test_eof329;
case 329:
#line 6960 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 89: goto tr413;
		case 121: goto tr413;
	}
	goto st0;
tr413:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st330;
st330:
	if ( ++p == pe )
		goto _test_eof330;
case 330:
#line 6980 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 76: goto tr414;
		case 82: goto tr415;
		case 83: goto tr416;
		case 108: goto tr414;
		case 114: goto tr415;
		case 115: goto tr416;
	}
	goto st0;
tr414:
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st331;
st331:
	if ( ++p == pe )
		goto _test_eof331;
case 331:
#line 7000 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr417;
		case 101: goto tr417;
	}
	goto st0;
tr417:
#line 169 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebylex; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st332;
st332:
	if ( ++p == pe )
		goto _test_eof332;
case 332:
#line 7016 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 88: goto tr418;
		case 120: goto tr418;
	}
	goto st0;
tr415:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st333;
st333:
	if ( ++p == pe )
		goto _test_eof333;
case 333:
#line 7032 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr419;
		case 97: goto tr419;
	}
	goto st0;
tr419:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st334;
st334:
	if ( ++p == pe )
		goto _test_eof334;
case 334:
#line 7048 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr420;
		case 110: goto tr420;
	}
	goto st0;
tr420:
#line 153 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st335;
st335:
	if ( ++p == pe )
		goto _test_eof335;
case 335:
#line 7064 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 75: goto tr421;
		case 107: goto tr421;
	}
	goto st0;
tr416:
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st336;
st336:
	if ( ++p == pe )
		goto _test_eof336;
case 336:
#line 7080 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr422;
		case 99: goto tr422;
	}
	goto st0;
tr422:
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st337;
st337:
	if ( ++p == pe )
		goto _test_eof337;
case 337:
#line 7096 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr423;
		case 111: goto tr423;
	}
	goto st0;
tr423:
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st338;
st338:
	if ( ++p == pe )
		goto _test_eof338;
case 338:
#line 7112 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr424;
		case 114: goto tr424;
	}
	goto st0;
tr424:
#line 154 "include/redis_protocol_parser.rl"
	{_command = command::zremrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st339;
st339:
	if ( ++p == pe )
		goto _test_eof339;
case 339:
#line 7128 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr425;
		case 101: goto tr425;
	}
	goto st0;
tr406:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 155 "include/redis_protocol_parser.rl"
	{_command = command::zrevrange; }
#line 157 "include/redis_protocol_parser.rl"
	{_command = command::zrevrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st340;
st340:
	if ( ++p == pe )
		goto _test_eof340;
case 340:
#line 7148 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr426;
		case 114: goto tr426;
	}
	goto st0;
tr426:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 155 "include/redis_protocol_parser.rl"
	{_command = command::zrevrange; }
#line 157 "include/redis_protocol_parser.rl"
	{_command = command::zrevrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st341;
st341:
	if ( ++p == pe )
		goto _test_eof341;
case 341:
#line 7168 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr427;
		case 97: goto tr427;
	}
	goto st0;
tr427:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 155 "include/redis_protocol_parser.rl"
	{_command = command::zrevrange; }
#line 157 "include/redis_protocol_parser.rl"
	{_command = command::zrevrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st342;
st342:
	if ( ++p == pe )
		goto _test_eof342;
case 342:
#line 7188 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr428;
		case 110: goto tr428;
	}
	goto st0;
tr428:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 155 "include/redis_protocol_parser.rl"
	{_command = command::zrevrange; }
#line 157 "include/redis_protocol_parser.rl"
	{_command = command::zrevrank; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st343;
st343:
	if ( ++p == pe )
		goto _test_eof343;
case 343:
#line 7208 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 71: goto tr429;
		case 75: goto tr430;
		case 103: goto tr429;
		case 107: goto tr430;
	}
	goto st0;
tr429:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 155 "include/redis_protocol_parser.rl"
	{_command = command::zrevrange; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st344;
st344:
	if ( ++p == pe )
		goto _test_eof344;
case 344:
#line 7228 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr431;
		case 101: goto tr431;
	}
	goto st0;
tr431:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 155 "include/redis_protocol_parser.rl"
	{_command = command::zrevrange; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st345;
st345:
	if ( ++p == pe )
		goto _test_eof345;
case 345:
#line 7246 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 66: goto tr432;
		case 98: goto tr432;
	}
	goto st0;
tr432:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st346;
st346:
	if ( ++p == pe )
		goto _test_eof346;
case 346:
#line 7263 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 89: goto tr433;
		case 121: goto tr433;
	}
	goto st0;
tr433:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st347;
st347:
	if ( ++p == pe )
		goto _test_eof347;
case 347:
#line 7279 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 83: goto tr434;
		case 115: goto tr434;
	}
	goto st0;
tr434:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st348;
st348:
	if ( ++p == pe )
		goto _test_eof348;
case 348:
#line 7295 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr435;
		case 99: goto tr435;
	}
	goto st0;
tr435:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st349;
st349:
	if ( ++p == pe )
		goto _test_eof349;
case 349:
#line 7311 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr436;
		case 111: goto tr436;
	}
	goto st0;
tr436:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st350;
st350:
	if ( ++p == pe )
		goto _test_eof350;
case 350:
#line 7327 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr437;
		case 114: goto tr437;
	}
	goto st0;
tr437:
#line 156 "include/redis_protocol_parser.rl"
	{_command = command::zrevrangebyscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st351;
st351:
	if ( ++p == pe )
		goto _test_eof351;
case 351:
#line 7343 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr438;
		case 101: goto tr438;
	}
	goto st0;
tr350:
#line 158 "include/redis_protocol_parser.rl"
	{_command = command::zscore; }
#line 165 "include/redis_protocol_parser.rl"
	{_command = command::zscan; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st352;
st352:
	if ( ++p == pe )
		goto _test_eof352;
case 352:
#line 7361 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 67: goto tr439;
		case 99: goto tr439;
	}
	goto st0;
tr439:
#line 158 "include/redis_protocol_parser.rl"
	{_command = command::zscore; }
#line 165 "include/redis_protocol_parser.rl"
	{_command = command::zscan; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st353;
st353:
	if ( ++p == pe )
		goto _test_eof353;
case 353:
#line 7379 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 65: goto tr440;
		case 79: goto tr441;
		case 97: goto tr440;
		case 111: goto tr441;
	}
	goto st0;
tr440:
#line 165 "include/redis_protocol_parser.rl"
	{_command = command::zscan; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st354;
st354:
	if ( ++p == pe )
		goto _test_eof354;
case 354:
#line 7397 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr442;
		case 110: goto tr442;
	}
	goto st0;
tr441:
#line 158 "include/redis_protocol_parser.rl"
	{_command = command::zscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st355;
st355:
	if ( ++p == pe )
		goto _test_eof355;
case 355:
#line 7413 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr443;
		case 114: goto tr443;
	}
	goto st0;
tr443:
#line 158 "include/redis_protocol_parser.rl"
	{_command = command::zscore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st356;
st356:
	if ( ++p == pe )
		goto _test_eof356;
case 356:
#line 7429 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr444;
		case 101: goto tr444;
	}
	goto st0;
tr351:
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 162 "include/redis_protocol_parser.rl"
	{_command = command::zunion; }
#line 164 "include/redis_protocol_parser.rl"
	{_command = command::zdiff; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st357;
st357:
	if ( ++p == pe )
		goto _test_eof357;
case 357:
#line 7449 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr445;
		case 110: goto tr445;
	}
	goto st0;
tr445:
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 162 "include/redis_protocol_parser.rl"
	{_command = command::zunion; }
#line 164 "include/redis_protocol_parser.rl"
	{_command = command::zdiff; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st358;
st358:
	if ( ++p == pe )
		goto _test_eof358;
case 358:
#line 7469 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 73: goto tr446;
		case 105: goto tr446;
	}
	goto st0;
tr446:
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 162 "include/redis_protocol_parser.rl"
	{_command = command::zunion; }
#line 164 "include/redis_protocol_parser.rl"
	{_command = command::zdiff; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st359;
st359:
	if ( ++p == pe )
		goto _test_eof359;
case 359:
#line 7489 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr447;
		case 111: goto tr447;
	}
	goto st0;
tr447:
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 162 "include/redis_protocol_parser.rl"
	{_command = command::zunion; }
#line 164 "include/redis_protocol_parser.rl"
	{_command = command::zdiff; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st360;
st360:
	if ( ++p == pe )
		goto _test_eof360;
case 360:
#line 7509 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 78: goto tr448;
		case 110: goto tr448;
	}
	goto st0;
tr448:
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 162 "include/redis_protocol_parser.rl"
	{_command = command::zunion; }
#line 164 "include/redis_protocol_parser.rl"
	{_command = command::zdiff; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st361;
st361:
	if ( ++p == pe )
		goto _test_eof361;
case 361:
#line 7529 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 13: goto tr33;
		case 83: goto tr449;
		case 115: goto tr449;
	}
	goto st0;
tr449:
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st362;
st362:
	if ( ++p == pe )
		goto _test_eof362;
case 362:
#line 7546 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 84: goto tr450;
		case 116: goto tr450;
	}
	goto st0;
tr450:
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st363;
st363:
	if ( ++p == pe )
		goto _test_eof363;
case 363:
#line 7562 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 79: goto tr451;
		case 111: goto tr451;
	}
	goto st0;
tr451:
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st364;
st364:
	if ( ++p == pe )
		goto _test_eof364;
case 364:
#line 7578 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 82: goto tr452;
		case 114: goto tr452;
	}
	goto st0;
tr452:
#line 159 "include/redis_protocol_parser.rl"
	{_command = command::zunionstore; }
#line 199 "include/redis_protocol_parser.rl"
	{_state = state::ok;}
	goto st365;
st365:
	if ( ++p == pe )
		goto _test_eof365;
case 365:
#line 7594 "include/redis_protocol_parser.hh"
	switch( (*p) ) {
		case 69: goto tr453;
		case 101: goto tr453;
	}
	goto st0;
st366:
	if ( ++p == pe )
		goto _test_eof366;
case 366:
	goto tr454;
tr454:
#line 44 "include/redis_protocol_parser.rl"
	{
    g.mark_start(p);
    _size_left = _arg_size;
}
#line 53 "include/redis_protocol_parser.rl"
	{
    auto len = std::min((uint32_t)(pe - p), _size_left);
    _size_left -= len;
    p += len;
    if (_size_left == 0) {
      _args_list.push_back(str());
      p--;
      { _fsm_cs =  _fsm_stack[-- _fsm_top];{
    postpop();
}goto _again;}
    }
    p--;
}
	goto st368;
tr455:
#line 53 "include/redis_protocol_parser.rl"
	{
    auto len = std::min((uint32_t)(pe - p), _size_left);
    _size_left -= len;
    p += len;
    if (_size_left == 0) {
      _args_list.push_back(str());
      p--;
      { _fsm_cs =  _fsm_stack[-- _fsm_top];{
    postpop();
}goto _again;}
    }
    p--;
}
	goto st368;
st368:
	if ( ++p == pe )
		goto _test_eof368;
case 368:
#line 7646 "include/redis_protocol_parser.hh"
	goto tr455;
	}
	_test_eof1:  _fsm_cs = 1; goto _test_eof; 
	_test_eof2:  _fsm_cs = 2; goto _test_eof; 
	_test_eof3:  _fsm_cs = 3; goto _test_eof; 
	_test_eof4:  _fsm_cs = 4; goto _test_eof; 
	_test_eof5:  _fsm_cs = 5; goto _test_eof; 
	_test_eof6:  _fsm_cs = 6; goto _test_eof; 
	_test_eof7:  _fsm_cs = 7; goto _test_eof; 
	_test_eof8:  _fsm_cs = 8; goto _test_eof; 
	_test_eof9:  _fsm_cs = 9; goto _test_eof; 
	_test_eof10:  _fsm_cs = 10; goto _test_eof; 
	_test_eof11:  _fsm_cs = 11; goto _test_eof; 
	_test_eof12:  _fsm_cs = 12; goto _test_eof; 
	_test_eof13:  _fsm_cs = 13; goto _test_eof; 
	_test_eof14:  _fsm_cs = 14; goto _test_eof; 
	_test_eof15:  _fsm_cs = 15; goto _test_eof; 
	_test_eof16:  _fsm_cs = 16; goto _test_eof; 
	_test_eof17:  _fsm_cs = 17; goto _test_eof; 
	_test_eof18:  _fsm_cs = 18; goto _test_eof; 
	_test_eof19:  _fsm_cs = 19; goto _test_eof; 
	_test_eof20:  _fsm_cs = 20; goto _test_eof; 
	_test_eof21:  _fsm_cs = 21; goto _test_eof; 
	_test_eof22:  _fsm_cs = 22; goto _test_eof; 
	_test_eof367:  _fsm_cs = 367; goto _test_eof; 
	_test_eof23:  _fsm_cs = 23; goto _test_eof; 
	_test_eof24:  _fsm_cs = 24; goto _test_eof; 
	_test_eof25:  _fsm_cs = 25; goto _test_eof; 
	_test_eof26:  _fsm_cs = 26; goto _test_eof; 
	_test_eof27:  _fsm_cs = 27; goto _test_eof; 
	_test_eof28:  _fsm_cs = 28; goto _test_eof; 
	_test_eof29:  _fsm_cs = 29; goto _test_eof; 
	_test_eof30:  _fsm_cs = 30; goto _test_eof; 
	_test_eof31:  _fsm_cs = 31; goto _test_eof; 
	_test_eof32:  _fsm_cs = 32; goto _test_eof; 
	_test_eof33:  _fsm_cs = 33; goto _test_eof; 
	_test_eof34:  _fsm_cs = 34; goto _test_eof; 
	_test_eof35:  _fsm_cs = 35; goto _test_eof; 
	_test_eof36:  _fsm_cs = 36; goto _test_eof; 
	_test_eof37:  _fsm_cs = 37; goto _test_eof; 
	_test_eof38:  _fsm_cs = 38; goto _test_eof; 
	_test_eof39:  _fsm_cs = 39; goto _test_eof; 
	_test_eof40:  _fsm_cs = 40; goto _test_eof; 
	_test_eof41:  _fsm_cs = 41; goto _test_eof; 
	_test_eof42:  _fsm_cs = 42; goto _test_eof; 
	_test_eof43:  _fsm_cs = 43; goto _test_eof; 
	_test_eof44:  _fsm_cs = 44; goto _test_eof; 
	_test_eof45:  _fsm_cs = 45; goto _test_eof; 
	_test_eof46:  _fsm_cs = 46; goto _test_eof; 
	_test_eof47:  _fsm_cs = 47; goto _test_eof; 
	_test_eof48:  _fsm_cs = 48; goto _test_eof; 
	_test_eof49:  _fsm_cs = 49; goto _test_eof; 
	_test_eof50:  _fsm_cs = 50; goto _test_eof; 
	_test_eof51:  _fsm_cs = 51; goto _test_eof; 
	_test_eof52:  _fsm_cs = 52; goto _test_eof; 
	_test_eof53:  _fsm_cs = 53; goto _test_eof; 
	_test_eof54:  _fsm_cs = 54; goto _test_eof; 
	_test_eof55:  _fsm_cs = 55; goto _test_eof; 
	_test_eof56:  _fsm_cs = 56; goto _test_eof; 
	_test_eof57:  _fsm_cs = 57; goto _test_eof; 
	_test_eof58:  _fsm_cs = 58; goto _test_eof; 
	_test_eof59:  _fsm_cs = 59; goto _test_eof; 
	_test_eof60:  _fsm_cs = 60; goto _test_eof; 
	_test_eof61:  _fsm_cs = 61; goto _test_eof; 
	_test_eof62:  _fsm_cs = 62; goto _test_eof; 
	_test_eof63:  _fsm_cs = 63; goto _test_eof; 
	_test_eof64:  _fsm_cs = 64; goto _test_eof; 
	_test_eof65:  _fsm_cs = 65; goto _test_eof; 
	_test_eof66:  _fsm_cs = 66; goto _test_eof; 
	_test_eof67:  _fsm_cs = 67; goto _test_eof; 
	_test_eof68:  _fsm_cs = 68; goto _test_eof; 
	_test_eof69:  _fsm_cs = 69; goto _test_eof; 
	_test_eof70:  _fsm_cs = 70; goto _test_eof; 
	_test_eof71:  _fsm_cs = 71; goto _test_eof; 
	_test_eof72:  _fsm_cs = 72; goto _test_eof; 
	_test_eof73:  _fsm_cs = 73; goto _test_eof; 
	_test_eof74:  _fsm_cs = 74; goto _test_eof; 
	_test_eof75:  _fsm_cs = 75; goto _test_eof; 
	_test_eof76:  _fsm_cs = 76; goto _test_eof; 
	_test_eof77:  _fsm_cs = 77; goto _test_eof; 
	_test_eof78:  _fsm_cs = 78; goto _test_eof; 
	_test_eof79:  _fsm_cs = 79; goto _test_eof; 
	_test_eof80:  _fsm_cs = 80; goto _test_eof; 
	_test_eof81:  _fsm_cs = 81; goto _test_eof; 
	_test_eof82:  _fsm_cs = 82; goto _test_eof; 
	_test_eof83:  _fsm_cs = 83; goto _test_eof; 
	_test_eof84:  _fsm_cs = 84; goto _test_eof; 
	_test_eof85:  _fsm_cs = 85; goto _test_eof; 
	_test_eof86:  _fsm_cs = 86; goto _test_eof; 
	_test_eof87:  _fsm_cs = 87; goto _test_eof; 
	_test_eof88:  _fsm_cs = 88; goto _test_eof; 
	_test_eof89:  _fsm_cs = 89; goto _test_eof; 
	_test_eof90:  _fsm_cs = 90; goto _test_eof; 
	_test_eof91:  _fsm_cs = 91; goto _test_eof; 
	_test_eof92:  _fsm_cs = 92; goto _test_eof; 
	_test_eof93:  _fsm_cs = 93; goto _test_eof; 
	_test_eof94:  _fsm_cs = 94; goto _test_eof; 
	_test_eof95:  _fsm_cs = 95; goto _test_eof; 
	_test_eof96:  _fsm_cs = 96; goto _test_eof; 
	_test_eof97:  _fsm_cs = 97; goto _test_eof; 
	_test_eof98:  _fsm_cs = 98; goto _test_eof; 
	_test_eof99:  _fsm_cs = 99; goto _test_eof; 
	_test_eof100:  _fsm_cs = 100; goto _test_eof; 
	_test_eof101:  _fsm_cs = 101; goto _test_eof; 
	_test_eof102:  _fsm_cs = 102; goto _test_eof; 
	_test_eof103:  _fsm_cs = 103; goto _test_eof; 
	_test_eof104:  _fsm_cs = 104; goto _test_eof; 
	_test_eof105:  _fsm_cs = 105; goto _test_eof; 
	_test_eof106:  _fsm_cs = 106; goto _test_eof; 
	_test_eof107:  _fsm_cs = 107; goto _test_eof; 
	_test_eof108:  _fsm_cs = 108; goto _test_eof; 
	_test_eof109:  _fsm_cs = 109; goto _test_eof; 
	_test_eof110:  _fsm_cs = 110; goto _test_eof; 
	_test_eof111:  _fsm_cs = 111; goto _test_eof; 
	_test_eof112:  _fsm_cs = 112; goto _test_eof; 
	_test_eof113:  _fsm_cs = 113; goto _test_eof; 
	_test_eof114:  _fsm_cs = 114; goto _test_eof; 
	_test_eof115:  _fsm_cs = 115; goto _test_eof; 
	_test_eof116:  _fsm_cs = 116; goto _test_eof; 
	_test_eof117:  _fsm_cs = 117; goto _test_eof; 
	_test_eof118:  _fsm_cs = 118; goto _test_eof; 
	_test_eof119:  _fsm_cs = 119; goto _test_eof; 
	_test_eof120:  _fsm_cs = 120; goto _test_eof; 
	_test_eof121:  _fsm_cs = 121; goto _test_eof; 
	_test_eof122:  _fsm_cs = 122; goto _test_eof; 
	_test_eof123:  _fsm_cs = 123; goto _test_eof; 
	_test_eof124:  _fsm_cs = 124; goto _test_eof; 
	_test_eof125:  _fsm_cs = 125; goto _test_eof; 
	_test_eof126:  _fsm_cs = 126; goto _test_eof; 
	_test_eof127:  _fsm_cs = 127; goto _test_eof; 
	_test_eof128:  _fsm_cs = 128; goto _test_eof; 
	_test_eof129:  _fsm_cs = 129; goto _test_eof; 
	_test_eof130:  _fsm_cs = 130; goto _test_eof; 
	_test_eof131:  _fsm_cs = 131; goto _test_eof; 
	_test_eof132:  _fsm_cs = 132; goto _test_eof; 
	_test_eof133:  _fsm_cs = 133; goto _test_eof; 
	_test_eof134:  _fsm_cs = 134; goto _test_eof; 
	_test_eof135:  _fsm_cs = 135; goto _test_eof; 
	_test_eof136:  _fsm_cs = 136; goto _test_eof; 
	_test_eof137:  _fsm_cs = 137; goto _test_eof; 
	_test_eof138:  _fsm_cs = 138; goto _test_eof; 
	_test_eof139:  _fsm_cs = 139; goto _test_eof; 
	_test_eof140:  _fsm_cs = 140; goto _test_eof; 
	_test_eof141:  _fsm_cs = 141; goto _test_eof; 
	_test_eof142:  _fsm_cs = 142; goto _test_eof; 
	_test_eof143:  _fsm_cs = 143; goto _test_eof; 
	_test_eof144:  _fsm_cs = 144; goto _test_eof; 
	_test_eof145:  _fsm_cs = 145; goto _test_eof; 
	_test_eof146:  _fsm_cs = 146; goto _test_eof; 
	_test_eof147:  _fsm_cs = 147; goto _test_eof; 
	_test_eof148:  _fsm_cs = 148; goto _test_eof; 
	_test_eof149:  _fsm_cs = 149; goto _test_eof; 
	_test_eof150:  _fsm_cs = 150; goto _test_eof; 
	_test_eof151:  _fsm_cs = 151; goto _test_eof; 
	_test_eof152:  _fsm_cs = 152; goto _test_eof; 
	_test_eof153:  _fsm_cs = 153; goto _test_eof; 
	_test_eof154:  _fsm_cs = 154; goto _test_eof; 
	_test_eof155:  _fsm_cs = 155; goto _test_eof; 
	_test_eof156:  _fsm_cs = 156; goto _test_eof; 
	_test_eof157:  _fsm_cs = 157; goto _test_eof; 
	_test_eof158:  _fsm_cs = 158; goto _test_eof; 
	_test_eof159:  _fsm_cs = 159; goto _test_eof; 
	_test_eof160:  _fsm_cs = 160; goto _test_eof; 
	_test_eof161:  _fsm_cs = 161; goto _test_eof; 
	_test_eof162:  _fsm_cs = 162; goto _test_eof; 
	_test_eof163:  _fsm_cs = 163; goto _test_eof; 
	_test_eof164:  _fsm_cs = 164; goto _test_eof; 
	_test_eof165:  _fsm_cs = 165; goto _test_eof; 
	_test_eof166:  _fsm_cs = 166; goto _test_eof; 
	_test_eof167:  _fsm_cs = 167; goto _test_eof; 
	_test_eof168:  _fsm_cs = 168; goto _test_eof; 
	_test_eof169:  _fsm_cs = 169; goto _test_eof; 
	_test_eof170:  _fsm_cs = 170; goto _test_eof; 
	_test_eof171:  _fsm_cs = 171; goto _test_eof; 
	_test_eof172:  _fsm_cs = 172; goto _test_eof; 
	_test_eof173:  _fsm_cs = 173; goto _test_eof; 
	_test_eof174:  _fsm_cs = 174; goto _test_eof; 
	_test_eof175:  _fsm_cs = 175; goto _test_eof; 
	_test_eof176:  _fsm_cs = 176; goto _test_eof; 
	_test_eof177:  _fsm_cs = 177; goto _test_eof; 
	_test_eof178:  _fsm_cs = 178; goto _test_eof; 
	_test_eof179:  _fsm_cs = 179; goto _test_eof; 
	_test_eof180:  _fsm_cs = 180; goto _test_eof; 
	_test_eof181:  _fsm_cs = 181; goto _test_eof; 
	_test_eof182:  _fsm_cs = 182; goto _test_eof; 
	_test_eof183:  _fsm_cs = 183; goto _test_eof; 
	_test_eof184:  _fsm_cs = 184; goto _test_eof; 
	_test_eof185:  _fsm_cs = 185; goto _test_eof; 
	_test_eof186:  _fsm_cs = 186; goto _test_eof; 
	_test_eof187:  _fsm_cs = 187; goto _test_eof; 
	_test_eof188:  _fsm_cs = 188; goto _test_eof; 
	_test_eof189:  _fsm_cs = 189; goto _test_eof; 
	_test_eof190:  _fsm_cs = 190; goto _test_eof; 
	_test_eof191:  _fsm_cs = 191; goto _test_eof; 
	_test_eof192:  _fsm_cs = 192; goto _test_eof; 
	_test_eof193:  _fsm_cs = 193; goto _test_eof; 
	_test_eof194:  _fsm_cs = 194; goto _test_eof; 
	_test_eof195:  _fsm_cs = 195; goto _test_eof; 
	_test_eof196:  _fsm_cs = 196; goto _test_eof; 
	_test_eof197:  _fsm_cs = 197; goto _test_eof; 
	_test_eof198:  _fsm_cs = 198; goto _test_eof; 
	_test_eof199:  _fsm_cs = 199; goto _test_eof; 
	_test_eof200:  _fsm_cs = 200; goto _test_eof; 
	_test_eof201:  _fsm_cs = 201; goto _test_eof; 
	_test_eof202:  _fsm_cs = 202; goto _test_eof; 
	_test_eof203:  _fsm_cs = 203; goto _test_eof; 
	_test_eof204:  _fsm_cs = 204; goto _test_eof; 
	_test_eof205:  _fsm_cs = 205; goto _test_eof; 
	_test_eof206:  _fsm_cs = 206; goto _test_eof; 
	_test_eof207:  _fsm_cs = 207; goto _test_eof; 
	_test_eof208:  _fsm_cs = 208; goto _test_eof; 
	_test_eof209:  _fsm_cs = 209; goto _test_eof; 
	_test_eof210:  _fsm_cs = 210; goto _test_eof; 
	_test_eof211:  _fsm_cs = 211; goto _test_eof; 
	_test_eof212:  _fsm_cs = 212; goto _test_eof; 
	_test_eof213:  _fsm_cs = 213; goto _test_eof; 
	_test_eof214:  _fsm_cs = 214; goto _test_eof; 
	_test_eof215:  _fsm_cs = 215; goto _test_eof; 
	_test_eof216:  _fsm_cs = 216; goto _test_eof; 
	_test_eof217:  _fsm_cs = 217; goto _test_eof; 
	_test_eof218:  _fsm_cs = 218; goto _test_eof; 
	_test_eof219:  _fsm_cs = 219; goto _test_eof; 
	_test_eof220:  _fsm_cs = 220; goto _test_eof; 
	_test_eof221:  _fsm_cs = 221; goto _test_eof; 
	_test_eof222:  _fsm_cs = 222; goto _test_eof; 
	_test_eof223:  _fsm_cs = 223; goto _test_eof; 
	_test_eof224:  _fsm_cs = 224; goto _test_eof; 
	_test_eof225:  _fsm_cs = 225; goto _test_eof; 
	_test_eof226:  _fsm_cs = 226; goto _test_eof; 
	_test_eof227:  _fsm_cs = 227; goto _test_eof; 
	_test_eof228:  _fsm_cs = 228; goto _test_eof; 
	_test_eof229:  _fsm_cs = 229; goto _test_eof; 
	_test_eof230:  _fsm_cs = 230; goto _test_eof; 
	_test_eof231:  _fsm_cs = 231; goto _test_eof; 
	_test_eof232:  _fsm_cs = 232; goto _test_eof; 
	_test_eof233:  _fsm_cs = 233; goto _test_eof; 
	_test_eof234:  _fsm_cs = 234; goto _test_eof; 
	_test_eof235:  _fsm_cs = 235; goto _test_eof; 
	_test_eof236:  _fsm_cs = 236; goto _test_eof; 
	_test_eof237:  _fsm_cs = 237; goto _test_eof; 
	_test_eof238:  _fsm_cs = 238; goto _test_eof; 
	_test_eof239:  _fsm_cs = 239; goto _test_eof; 
	_test_eof240:  _fsm_cs = 240; goto _test_eof; 
	_test_eof241:  _fsm_cs = 241; goto _test_eof; 
	_test_eof242:  _fsm_cs = 242; goto _test_eof; 
	_test_eof243:  _fsm_cs = 243; goto _test_eof; 
	_test_eof244:  _fsm_cs = 244; goto _test_eof; 
	_test_eof245:  _fsm_cs = 245; goto _test_eof; 
	_test_eof246:  _fsm_cs = 246; goto _test_eof; 
	_test_eof247:  _fsm_cs = 247; goto _test_eof; 
	_test_eof248:  _fsm_cs = 248; goto _test_eof; 
	_test_eof249:  _fsm_cs = 249; goto _test_eof; 
	_test_eof250:  _fsm_cs = 250; goto _test_eof; 
	_test_eof251:  _fsm_cs = 251; goto _test_eof; 
	_test_eof252:  _fsm_cs = 252; goto _test_eof; 
	_test_eof253:  _fsm_cs = 253; goto _test_eof; 
	_test_eof254:  _fsm_cs = 254; goto _test_eof; 
	_test_eof255:  _fsm_cs = 255; goto _test_eof; 
	_test_eof256:  _fsm_cs = 256; goto _test_eof; 
	_test_eof257:  _fsm_cs = 257; goto _test_eof; 
	_test_eof258:  _fsm_cs = 258; goto _test_eof; 
	_test_eof259:  _fsm_cs = 259; goto _test_eof; 
	_test_eof260:  _fsm_cs = 260; goto _test_eof; 
	_test_eof261:  _fsm_cs = 261; goto _test_eof; 
	_test_eof262:  _fsm_cs = 262; goto _test_eof; 
	_test_eof263:  _fsm_cs = 263; goto _test_eof; 
	_test_eof264:  _fsm_cs = 264; goto _test_eof; 
	_test_eof265:  _fsm_cs = 265; goto _test_eof; 
	_test_eof266:  _fsm_cs = 266; goto _test_eof; 
	_test_eof267:  _fsm_cs = 267; goto _test_eof; 
	_test_eof268:  _fsm_cs = 268; goto _test_eof; 
	_test_eof269:  _fsm_cs = 269; goto _test_eof; 
	_test_eof270:  _fsm_cs = 270; goto _test_eof; 
	_test_eof271:  _fsm_cs = 271; goto _test_eof; 
	_test_eof272:  _fsm_cs = 272; goto _test_eof; 
	_test_eof273:  _fsm_cs = 273; goto _test_eof; 
	_test_eof274:  _fsm_cs = 274; goto _test_eof; 
	_test_eof275:  _fsm_cs = 275; goto _test_eof; 
	_test_eof276:  _fsm_cs = 276; goto _test_eof; 
	_test_eof277:  _fsm_cs = 277; goto _test_eof; 
	_test_eof278:  _fsm_cs = 278; goto _test_eof; 
	_test_eof279:  _fsm_cs = 279; goto _test_eof; 
	_test_eof280:  _fsm_cs = 280; goto _test_eof; 
	_test_eof281:  _fsm_cs = 281; goto _test_eof; 
	_test_eof282:  _fsm_cs = 282; goto _test_eof; 
	_test_eof283:  _fsm_cs = 283; goto _test_eof; 
	_test_eof284:  _fsm_cs = 284; goto _test_eof; 
	_test_eof285:  _fsm_cs = 285; goto _test_eof; 
	_test_eof286:  _fsm_cs = 286; goto _test_eof; 
	_test_eof287:  _fsm_cs = 287; goto _test_eof; 
	_test_eof288:  _fsm_cs = 288; goto _test_eof; 
	_test_eof289:  _fsm_cs = 289; goto _test_eof; 
	_test_eof290:  _fsm_cs = 290; goto _test_eof; 
	_test_eof291:  _fsm_cs = 291; goto _test_eof; 
	_test_eof292:  _fsm_cs = 292; goto _test_eof; 
	_test_eof293:  _fsm_cs = 293; goto _test_eof; 
	_test_eof294:  _fsm_cs = 294; goto _test_eof; 
	_test_eof295:  _fsm_cs = 295; goto _test_eof; 
	_test_eof296:  _fsm_cs = 296; goto _test_eof; 
	_test_eof297:  _fsm_cs = 297; goto _test_eof; 
	_test_eof298:  _fsm_cs = 298; goto _test_eof; 
	_test_eof299:  _fsm_cs = 299; goto _test_eof; 
	_test_eof300:  _fsm_cs = 300; goto _test_eof; 
	_test_eof301:  _fsm_cs = 301; goto _test_eof; 
	_test_eof302:  _fsm_cs = 302; goto _test_eof; 
	_test_eof303:  _fsm_cs = 303; goto _test_eof; 
	_test_eof304:  _fsm_cs = 304; goto _test_eof; 
	_test_eof305:  _fsm_cs = 305; goto _test_eof; 
	_test_eof306:  _fsm_cs = 306; goto _test_eof; 
	_test_eof307:  _fsm_cs = 307; goto _test_eof; 
	_test_eof308:  _fsm_cs = 308; goto _test_eof; 
	_test_eof309:  _fsm_cs = 309; goto _test_eof; 
	_test_eof310:  _fsm_cs = 310; goto _test_eof; 
	_test_eof311:  _fsm_cs = 311; goto _test_eof; 
	_test_eof312:  _fsm_cs = 312; goto _test_eof; 
	_test_eof313:  _fsm_cs = 313; goto _test_eof; 
	_test_eof314:  _fsm_cs = 314; goto _test_eof; 
	_test_eof315:  _fsm_cs = 315; goto _test_eof; 
	_test_eof316:  _fsm_cs = 316; goto _test_eof; 
	_test_eof317:  _fsm_cs = 317; goto _test_eof; 
	_test_eof318:  _fsm_cs = 318; goto _test_eof; 
	_test_eof319:  _fsm_cs = 319; goto _test_eof; 
	_test_eof320:  _fsm_cs = 320; goto _test_eof; 
	_test_eof321:  _fsm_cs = 321; goto _test_eof; 
	_test_eof322:  _fsm_cs = 322; goto _test_eof; 
	_test_eof323:  _fsm_cs = 323; goto _test_eof; 
	_test_eof324:  _fsm_cs = 324; goto _test_eof; 
	_test_eof325:  _fsm_cs = 325; goto _test_eof; 
	_test_eof326:  _fsm_cs = 326; goto _test_eof; 
	_test_eof327:  _fsm_cs = 327; goto _test_eof; 
	_test_eof328:  _fsm_cs = 328; goto _test_eof; 
	_test_eof329:  _fsm_cs = 329; goto _test_eof; 
	_test_eof330:  _fsm_cs = 330; goto _test_eof; 
	_test_eof331:  _fsm_cs = 331; goto _test_eof; 
	_test_eof332:  _fsm_cs = 332; goto _test_eof; 
	_test_eof333:  _fsm_cs = 333; goto _test_eof; 
	_test_eof334:  _fsm_cs = 334; goto _test_eof; 
	_test_eof335:  _fsm_cs = 335; goto _test_eof; 
	_test_eof336:  _fsm_cs = 336; goto _test_eof; 
	_test_eof337:  _fsm_cs = 337; goto _test_eof; 
	_test_eof338:  _fsm_cs = 338; goto _test_eof; 
	_test_eof339:  _fsm_cs = 339; goto _test_eof; 
	_test_eof340:  _fsm_cs = 340; goto _test_eof; 
	_test_eof341:  _fsm_cs = 341; goto _test_eof; 
	_test_eof342:  _fsm_cs = 342; goto _test_eof; 
	_test_eof343:  _fsm_cs = 343; goto _test_eof; 
	_test_eof344:  _fsm_cs = 344; goto _test_eof; 
	_test_eof345:  _fsm_cs = 345; goto _test_eof; 
	_test_eof346:  _fsm_cs = 346; goto _test_eof; 
	_test_eof347:  _fsm_cs = 347; goto _test_eof; 
	_test_eof348:  _fsm_cs = 348; goto _test_eof; 
	_test_eof349:  _fsm_cs = 349; goto _test_eof; 
	_test_eof350:  _fsm_cs = 350; goto _test_eof; 
	_test_eof351:  _fsm_cs = 351; goto _test_eof; 
	_test_eof352:  _fsm_cs = 352; goto _test_eof; 
	_test_eof353:  _fsm_cs = 353; goto _test_eof; 
	_test_eof354:  _fsm_cs = 354; goto _test_eof; 
	_test_eof355:  _fsm_cs = 355; goto _test_eof; 
	_test_eof356:  _fsm_cs = 356; goto _test_eof; 
	_test_eof357:  _fsm_cs = 357; goto _test_eof; 
	_test_eof358:  _fsm_cs = 358; goto _test_eof; 
	_test_eof359:  _fsm_cs = 359; goto _test_eof; 
	_test_eof360:  _fsm_cs = 360; goto _test_eof; 
	_test_eof361:  _fsm_cs = 361; goto _test_eof; 
	_test_eof362:  _fsm_cs = 362; goto _test_eof; 
	_test_eof363:  _fsm_cs = 363; goto _test_eof; 
	_test_eof364:  _fsm_cs = 364; goto _test_eof; 
	_test_eof365:  _fsm_cs = 365; goto _test_eof; 
	_test_eof366:  _fsm_cs = 366; goto _test_eof; 
	_test_eof368:  _fsm_cs = 368; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 348 "include/redis_protocol_parser.rl"
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
