## Notes from vikbez
This project was found deep on the interwebs.

This is an encoder/decoder for ShowView and VCR+ codes.
It has some limitations but it kind of works.

You'll find below the contents of the GENERAL file that was included with the project, explaining how ShowView and VCR+ works.

## General
Showview is the german version of a system which started in the 'States a couple of years ago under the name VCR+. There is also a UK version called Videoplus. All these names are registered trade names of GemStar Inc.

The goal of the system is to encode the day-number, channel number and the *published* start time and duration of a TV programme as a number of no more than 9 digits such that the encoding can be called proprietary, and that Gem-Star can raise revenue by selling the codes to newspapers. They also licence use of the system to be built into VCRs and stand-alone decoder handsets.

Codes are cunningly arranged to be small numbers in the case of prime-time material and progressively longer numbers for the more obscure time slots. It is done by arranging popular timeslots to be earliest in a giant lookup table.

## TV Schedule differences
Because the US, UK and Euro ideas of television scheduling differ, different variants of VCR+ exist. All three systems use different loopup tables and a different bit shuffling (see below).

The US arrange 99% of their programming to start and end on 30-minute boundaries, frequently have programmes with lengths up to and including five hours (American Football or Baseball) and have a *lot* of channel numbers to choose from. There are thus 480 timeslots on 48 channels which get 6 digit-or-fewer codes in VCR+. There are 8 timeslots on the first 4 channels which get 3 digit-or-fewer codes in VCR+.

There are 2000 timeslots on 16 channels which get the 6-digit treatment in Videoplus because in the UK they use fewer channels on the whole but have a lot more variety in program length. As with VCR+ , there are 8 timeslots on the first 4 channels which can get 3 digit-or-fewer codes.

6-digit codes cover 1023 timeslots on 32 channels in Showview for the same reason. As with VCR+ and Videoplus, there are 8 timeslots on the first 4 channels (ARD, ZDF, ARD Bremen, RTL) which can get 3 digit-or-fewer codes.

Programmes whose starts and durations give them indexes 0-127 on the lookup table, and which are on channels 1-16 will actually have the same codes in VCR+ and Videoplus. This means all the 1,2,3 and 4-digit codes, plus some of the 5-digit codes are the same in the two systems. But Showview uses a completely different lookup table!

## Trivia
The following trivia hold for all three systems:
1) One-digit codes can only occur on the first of the month.
2) Two-digit codes can only occur on the 1st,2nd,3rd and 4th of the month, but there will only be 4 possible slots on the 4th of the month that can have a two-digit code.
3) A timeslot/channel combination which gets a one-digit code on the 1st of the month *will* get a 2 digit code on the 2nd and 3rd day, but not necessarily on the 4th.
4) A timeslot/channel combination which does get a two-digit code on the 4th of the month will have had a two-digit code on the 2nd and 3rd too, and may have had a one-digit or two-digit code on the 1st.

## Dates
Encoded along with the channel number and timeslot index is a programme date (just a number from 1-31). A decoder will assume that if the decoded day number is less than yesterday's day number, then it really refers to next month. So, codes can be published up to 27-29 days in advance of the programme's broadcast. There are "illegal" codes in the system, referring to the non-existant dates at the end of certain months. Commercial decoders produce an error report if these codes are tried, though the internet codec will still encode and decode them. There also are a few "illegal" codes which could in theory be validly decoded as occuring on the 32nd of the month. These are not handled even on the internet codecs though.

## Credits
VCR+ encoding was originally partly broken by a couple of guys in the States, Ken Shirriff <shirriff@sprite.berkeley.edu>, and Curt Welch
<curt@oasys.dt.navy.mil> and their published sources on Internet were picked up by Steve Hosgood <iisteve@iifeak.swan.ac.uk> and Douggie McClaggan <mclaggan@movies.enet.dec.com> and were extended to cover Videoplus.
Me, Daniel Minder <minder@ostalb.de> discovered them and adapted them to Showview.

Neither of these published codecs can (yet) deal properly with codes of more than 6 digits. This is under investigation. Currently *some* videoplus 7 and 8 digit codes can be coded and encoded only if certain similar codes are 'learnt' for the month in question.

These notes partly copyright (C) 1994,1995 Steve Hosgood.
Adaption (C) 1997 Daniel Minder.

## Australian G-Codes:
To use G-Codes set your VCR channels to the following - ABC as 2; SEVEN & PRIME as 7; NINE & WIN as 9; TEN & TEN VIC as 10; SBS as 28. G-Codes also apply to REGIONAL programs unless indicated.


