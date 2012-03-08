# This make file can be usedS to build J as part of an Android project.
# The project it was created for is hosted on github at
# https://github.com/mdykman/jconsole_for_android .
# openj should be checked out into a seperate folder under 
# <project-root>/jni . That project is equipped with an Android.mk 
# file which will invoke this one.
# Further detais on building J within the Android
# context can be found in that project
#
# this has been built under Android 2.2, API level 8.

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := j

LOCAL_LDLIBS := -llog  -ldl -lm -lc 

LOCAL_CFLAGS := -O0  -fno-omit-frame-pointer -fno-strict-aliasing -fno-unwind-tables -fno-tree-vectorize -D_MISALIGN_BYTEVECTOR  -DNOASM  -DOPENJ -fPIC


LOCAL_SRC_FILES :=  a.c ab.c af.c ai.c am.c am1.c amn.c ao.c ap.c ar.c as.c au.c c.c ca.c cc.c cd.c cf.c cg.c ch.c cip.c cl.c cp.c cpdtsp.c cr.c crs.c \
	ct.c cu.c cv.c cx.c d.c dc.c dss.c dstop.c dsusp.c dtoa.c f.c f2.c i.c io.c j.c jdlllic.c k.c m.c mbx.c p.c pv.c px.c r.c rl.c rt.c s.c sc.c sl.c \
	sn.c t.c u.c v.c v0.c v1.c v2.c va1.c va2.c va2s.c vamultsp.c vb.c vbang.c vbit.c vcant.c vchar.c vcat.c vcatsp.c vcomp.c vcompsc.c vd.c vdx.c ve.c \
	vf.c vfft.c vfrom.c  vfromsp.c vg.c vgauss.c vgcomp.c vgranking.c vgsort.c vgsp.c vi.c viix.c visp.c vm.c vo.c vp.c vq.c vrand.c vrep.c vs.c vsb.c \
	vt.c vu.c vx.c vz.c w.c wc.c wn.c ws.c x.c x15.c xa.c xb.c xc.c xcrc.c xd.c xf.c xfmt.c xh.c xi.c xl.c xo.c xs.c xt.c xu.c \
	jconsole.c jeload.c jni/j-jni-interface.c

include $(BUILD_SHARED_LIBRARY)


include jni/openj-core/defs/Android.mk
