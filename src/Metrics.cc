/* Copyright (c) 2011 Stanford University
 *
 * Permission to use, copy, modify, and distribute this software for
 * any purpose with or without fee is hereby granted, provided that
 * the above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR(S) DISCLAIM ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 * AUTHORS BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "BenchUtil.h"
#include "Common.h"
#include "Metrics.h"
#include "Segment.h"

namespace RAMCloud {

namespace {
    /// See #metrics.
    Metrics _metrics;
};

/**
 * Stores recovery metrics.
 * This is a pointer for future expansion. It always points to the same Metrics
 * object now.
 */
Metrics* metrics = &_metrics;

/**
 * Dump the recovery metrics to #logger.
 * \param metrics
 *      Which metrics object to dump.
 */
void
dump(const Metrics* metrics)
{
    LOG(NOTICE, "Metrics:");
    // this file is automatically generated from scripts/metrics.py
#include "Metrics.in.cc"
    LOG(NOTICE, "End of Metrics");
}

/**
 * Reset the recovery metrics.
 * \param metrics
 *      Which metrics object to reset.
 * \param serverId
 *      The unique server ID for this process assigned by the coordinator.
 * \param serverRole
 *      The role of this server (0 = coordinator, 1 = master, 2 = backup).
 */
void
reset(Metrics* metrics, uint64_t serverId, uint64_t serverRole)
{
    metrics->~Metrics();
    new(metrics) Metrics();
    metrics->clockFrequency = getCyclesPerSecond();
    metrics->pid = getpid();
    metrics->serverId = serverId;
    metrics->serverRole = serverRole;
    metrics->segmentSize = Segment::SEGMENT_SIZE;
}

/**
 * Store metrics tracked on server side for Bench
 */
ServerStats serverStats;

}  // namespace RAMCloud
