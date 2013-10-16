/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// "liveMedia"
// Copyright (c) 1996-2011 Live Networks, Inc.  All rights reserved.
// A 'ServerMediaSubsession' object that creates new, unicast, "RTPSink"s
// on demand, from an MP3 audio track within a Matroska file.
// (Actually, MPEG-1 or MPEG-2 audio file should also work.)
// Implementation

#include "MP3AudioMatroskaFileServerMediaSubsession.hh"

MP3AudioMatroskaFileServerMediaSubsession* MP3AudioMatroskaFileServerMediaSubsession
::createNew(MatroskaFileServerDemux& demux, unsigned trackNumber, Boolean generateADUs, Interleaving* interleaving) {
  return new MP3AudioMatroskaFileServerMediaSubsession(demux, trackNumber, generateADUs, interleaving);
}

MP3AudioMatroskaFileServerMediaSubsession
::MP3AudioMatroskaFileServerMediaSubsession(MatroskaFileServerDemux& demux, unsigned trackNumber,
					    Boolean generateADUs, Interleaving* interleaving)
  : MP3AudioFileServerMediaSubsession(demux.envir(), demux.fileName(), False, generateADUs, interleaving),
    fOurDemux(demux), fTrackNumber(trackNumber) {
  fFileDuration = fOurDemux.fileDuration();
}

MP3AudioMatroskaFileServerMediaSubsession::~MP3AudioMatroskaFileServerMediaSubsession() {
}

void MP3AudioMatroskaFileServerMediaSubsession
::seekStreamSource(FramedSource* inputSource, double seekNPT, double streamDuration, u_int64_t& numBytes) {
  OnDemandServerMediaSubsession::seekStreamSource(inputSource, seekNPT, streamDuration, numBytes); // for now, we don't support seeking #####@@@@@
#if 0 //#####@@@@@
  FramedSource* sourceMP3Stream;
  ADUFromMP3Source* aduStream;
  getBaseStreams(inputSource, sourceMP3Stream, aduStream);

  if (aduStream != NULL) aduStream->resetInput(); // because we're about to seek within its source
#if 0 //#####@@@@@
  ((MatroskaDemuxedTrack*)sourceMP3Stream)->seekWithinFile(seekNPT, streamDuration);
#endif
#endif
}

void MP3AudioMatroskaFileServerMediaSubsession
::setStreamSourceScale(FramedSource* inputSource, float scale) {
  OnDemandServerMediaSubsession::setStreamSourceScale(inputSource, scale); // for now, we don't support scaling #####@@@@@
#if 0 //#####@@@@@
  FramedSource* sourceMP3Stream;
  ADUFromMP3Source* aduStream;
  getBaseStreams(inputSource, sourceMP3Stream, aduStream);

  if (aduStream == NULL) return; // because, in this case, the stream's not scalable

  int iScale = (int)scale;
  aduStream->setScaleFactor(iScale);
#if 0 //#####@@@@@
  ((MatroskaDemuxedTrack*)sourceMP3Stream)->setPresentationTimeScale(iScale);
#endif
#endif
}

FramedSource* MP3AudioMatroskaFileServerMediaSubsession
::createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate) {
  FramedSource* baseMP3Source = fOurDemux.newDemuxedTrack(clientSessionId, fTrackNumber);
  return createNewStreamSourceCommon(baseMP3Source, 0, estBitrate);
}

void MP3AudioMatroskaFileServerMediaSubsession::testScaleFactor(float& scale) {
  ServerMediaSubsession::testScaleFactor(scale); // for now, we don't support scaling #####@@@@@
}
