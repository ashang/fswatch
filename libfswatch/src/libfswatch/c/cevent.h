/*
 * Copyright (c) 2014-2015 Enrico M. Crisostomo
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef FSW__CEVENT_H
#  define FSW__CEVENT_H

#  include <ctime>

#  ifdef __cplusplus
extern "C"
{
#  endif

  /*
   * Each element of this enum represents a backend-agnostic change flag,
   * providing information about the different kind of changes an event refers
   * to.
   */
  enum fsw_event_flag
  {
    NoOp = 0,
    PlatformSpecific = (1 << 0),
    Created = (1 << 1),
    Updated = (1 << 2),
    Removed = (1 << 3),
    Renamed = (1 << 4),
    OwnerModified = (1 << 5),
    AttributeModified = (1 << 6),
    MovedFrom = (1 << 7),
    MovedTo = (1 << 8),
    IsFile = (1 << 9),
    IsDir = (1 << 10),
    IsSymLink = (1 << 11),
    Link = (1 << 12),
    Overflow = (1 << 13)
  };

  fsw_event_flag fsw_get_event_flag_by_name(const char * name);
  char * fsw_get_event_flag_name(const fsw_event_flag flag);

  /*
   * An file change event is represented as an instance of this struct where:
   *   - path is the path where the event was triggered.
   *   - evt_time the time when the event was triggered.
   *   - flags is an array of fsw_event_flag of size flags_num.
   *   - flags_num is the size of the flags array.
   */
  typedef struct fsw_cevent
  {
    char * path;
    time_t evt_time;
    fsw_event_flag * flags;
    unsigned int flags_num;
  } fsw_cevent;

  /*
   * A function pointer of type FSW_CEVENT_CALLBACK is used by the API as a
   * callback to provide information about received events.  The callback is
   * passed the following arguments:
   *   - events, a const pointer to an array of events of type const fsw_cevent.
   *   - event_num, the size of the *events array.
   *   - data, optional persisted data for a callback.
   *
   * The memory used by the fsw_cevent objects will be freed at the end of the
   * callback invocation.  A callback should copy such data instead of storing
   * a pointer to it.
   */
  typedef void (*FSW_CEVENT_CALLBACK)(fsw_cevent const * const events,
    const unsigned int event_num, void * data);

#  ifdef __cplusplus
}
#  endif

#endif  /* FSW__CEVENT_H */
